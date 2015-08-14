#include <cstdio>
#include <queue>
#include <iostream>
#include <memory>
#include <algorithm>

#include "lms/executionmanager.h"
#include "lms/datamanager.h"
#include "lms/module.h"
#include "lms/module_wrapper.h"
#include "lms/loader.h"
#include "lms/datamanager.h"
#include "lms/profiler.h"
#include "lms/logger.h"

namespace lms {

ExecutionManager::ExecutionManager(logging::Logger &rootLogger)
    : rootLogger(rootLogger), logger("EXECMGR", &rootLogger), m_numThreads(1),
      m_multithreading(false),
      valid(false), loader(rootLogger), dataManager(rootLogger, *this),
      m_messaging(), m_cycleCounter(-1), running(true),
      m_profiler(rootLogger) {
}

ExecutionManager::~ExecutionManager () {
    stopRunning();

    disableAllModules();
}

void ExecutionManager::disableAllModules() {
    for(ModuleList::reverse_iterator it = enabledModules.rbegin();
        it != enabledModules.rend(); ++it) {

        if(! (*it)->moduleInstance->deinitialize()) {
            logger.error("disableModule")
                    << "Deinitialize failed for module " << (*it)->name;
        }
    }

    for(ModuleList::reverse_iterator it = available.rbegin();
        it != available.rend(); ++it) {
        dataManager.releaseChannelsOf(*it);
        loader.unload(it->get());
    }

    enabledModules.clear();

    invalidate();
}

DataManager& ExecutionManager::getDataManager() {
    return dataManager;
}

void ExecutionManager::loop() {
    // Remove all messages from the message queue
    m_messaging.resetQueue();

    if(m_profiler.enabled()) {
        m_profiler.printStats();
    }

    m_cycleCounter ++;
    m_profiler.resetProfMeasurements();

    //validate the ExecutionManager
    validate();

    if(! m_multithreading) {
        //copy cycleList so it can be modified
        cycleListTmp = cycleList;

        Profiler::ModuleMeasurement measurement;

        //simple single list
        while(cycleListTmp.size() > 0){
            //Iter over all module-vectors and check if they can be executed
            for(size_t i = 0; i < cycleListTmp.size();i++){
                std::vector<Module*>& moduleV = cycleListTmp[i];
                if(moduleV.size() == 1){

                    if(m_profiler.enabled()) {
                        measurement.thread = 0;
                        measurement.module = moduleV[0]->getName();
                        measurement.begin = lms::extra::PrecisionTime::now();
                        measurement.expected = moduleV[0]->getExpectedRuntime();
                    }

                    moduleV[0]->cycle();

                    if(m_profiler.enabled()) {
                        measurement.end = lms::extra::PrecisionTime::now();
                        m_profiler.addProfMeasurement(measurement);
                    }

                    //remove module from others
                    for(std::vector<Module*>& moduleV2:cycleListTmp){
                        moduleV2.erase(std::remove(moduleV2.begin(),moduleV2.end(),moduleV[0]),moduleV2.end());
                    }
                    //remove moduleV from cycleList
                    cycleListTmp.erase(std::remove(cycleListTmp.begin(),cycleListTmp.end(),moduleV),cycleListTmp.end());
                    i--;

                }
            }
        }
    }else{
        logger.info() << "Cycle start";

        // if thread pool is not yet initialized then do it now
        if(threadPool.empty()) {
            for(int threadNum = 1; threadNum <= m_numThreads; threadNum++) {
                threadPool.push_back(std::thread([threadNum, this] () {
                    threadFunction(threadNum);
                }));
            }
        }

        {
            std::lock_guard<std::mutex> lck(mutex);
            // copy cycleList so it can be modified
            cycleListTmp = cycleList;
            numModulesToExecute = cycleListTmp.size();

            // inform all threads that there are new jobs to do
            cv.notify_all();
        }

        {
            // wait until the cycle list is empty
            /*std::unique_lock<std::mutex> lck(mutex);
            cv.wait(lck, [this] () {
                return numModulesToExecute == 0;
            });*/

            threadFunction(0);
        }

        logger.info() << "Cycle end";
    }

    // TODO load or unload modules or do anything else
    for(const std::string &message : messaging().receive("enableModule")) {
        enableModule(message, logging::LogLevel::WARN);
    }

    for(const std::string &message : messaging().receive("disableModule")) {
        disableModule(message);
    }

    for(const std::string &message : messaging().receive("reloadModule")) {
        disableModule(message);
        enableModule(message, logging::LogLevel::WARN);
    }
}

void ExecutionManager::threadFunction(int threadNum) {
    // Thread function

    std::unique_lock<std::mutex> lck(mutex);

    while(running) {
        // wait until something is in the cycleList
        cv.wait(lck, [this, threadNum]() {
            // the main thread stops
            if(threadNum == 0 && numModulesToExecute == 0) {
                return true;
            }

            return hasExecutableModules(threadNum);
        });

        if(numModulesToExecute == 0) {
            break;
        }

        Module* executableModule = nullptr;
        int executableModuleIndex = 0;

        for(size_t i = 0; i < cycleListTmp.size();i++){
            std::vector<Module*>& moduleV = cycleListTmp[i];
            if(moduleV.size() == 1) {
                ModuleWrapper::ExecutionType execType = moduleV[0]->getExecutionType();
                if((execType == ModuleWrapper::ONLY_MAIN_THREAD && threadNum == 0) ||
                        (execType == ModuleWrapper::NEVER_MAIN_THREAD && threadNum != 0)) {
                    executableModuleIndex = i;
                    executableModule = moduleV[0];
                    break;
                }
            }
        }

        if(executableModule != nullptr) {
            // if an executable module was found
            // then delete it from the cycleListTmp
            cycleListTmp.erase(cycleListTmp.begin() + executableModuleIndex);

            logger.info() << "Thread " << threadNum << " executes "
                          << executableModule->getName();

            // Profiling stuff
            Profiler::ModuleMeasurement measurement;
            if(m_profiler.enabled()) {
                measurement.thread = threadNum;
                measurement.module = executableModule->getName();
            }

            // now we can execute it
            lck.unlock();
            measurement.begin = lms::extra::PrecisionTime::now();
            executableModule->cycle();
            measurement.end = lms::extra::PrecisionTime::now();
            lck.lock();

            if(m_profiler.enabled()) {
                m_profiler.addProfMeasurement(measurement);
            }

            logger.info() << "Thread " << threadNum << " executed "
                             << executableModule->getName();

            // now we should delete the executed module from
            // the dependencies of other modules
            for(std::vector<Module*>& moduleV2:cycleListTmp){
                moduleV2.erase(std::remove(moduleV2.begin(),moduleV2.end(),executableModule),moduleV2.end());
            }

            numModulesToExecute --;

            // now inform our fellow threads that something new
            // can be executed
            cv.notify_all();
        }
    }
}

bool ExecutionManager::hasExecutableModules(int thread) {
    if(! running) {
        return true;
    }

    if(cycleListTmp.empty()) {
        return false;
    }

    for(size_t i = 0; i < cycleListTmp.size();i++){
        std::vector<Module*>& moduleV = cycleListTmp[i];
        if(moduleV.size() == 1) {
            ModuleWrapper::ExecutionType execType = moduleV[0]->getExecutionType();
            if(execType == ModuleWrapper::ONLY_MAIN_THREAD && thread == 0) {
                return true;
            } else if(execType == ModuleWrapper::NEVER_MAIN_THREAD && thread != 0) {
                return true;
            }
        }
    }

    return false;
}

void ExecutionManager::stopRunning() {
    {
        std::lock_guard<std::mutex> lck(mutex);
        running = false;
        cv.notify_all();
    }

    for(std::thread &th : threadPool) {
        th.join();
    }
}

void ExecutionManager::addAvailableModule(std::shared_ptr<ModuleWrapper> mod){
    for(std::shared_ptr<ModuleWrapper> modEntry : available) {
        if(modEntry->name == mod->name) {
            logger.error("addAvailableModule") << "Tried to add available "
                << "module " << mod->name << " but was already available.";
            return;
        }
    }

    available.push_back(mod);
}

void ExecutionManager::enableModule(const std::string &name, lms::logging::LogLevel minLogLevel){
    //Check if module is already enabled
    for(auto it:enabledModules){
        if(it->name == name){
            logger.error("enableModule") << "Module " << name << " is already enabled.";
            return;
        }
    }
    for(std::shared_ptr<ModuleWrapper> it:available){
        if(it->name == name){
            loader.load(it.get());
            Module *module = it->moduleInstance;
            module->initializeBase(&dataManager, &m_messaging, this, it, &rootLogger, minLogLevel);

            if(module->initialize()){
                enabledModules.push_back(it);
            }else{
                logger.error("enable Module") <<"Enabling Module "<< name << " failed";
            }
            invalidate();
            return;
        }
    }
    logger.error("enable Module") <<"Module " << name << "doesn't exist!";
}

/**Disable module with the given name, remove it from the cycle-queue */
bool ExecutionManager::disableModule(const std::string &name) {
    for(ModuleList::iterator it = enabledModules.begin();
        it != enabledModules.end(); ++it) {

        if((*it)->name == name) {
            if(! (*it)->moduleInstance->deinitialize()) {
                logger.error("disableModule")
                        << "Deinitialize failed for module " << name;
            }

            for(std::shared_ptr<ModuleWrapper> entry : available) {
                if(entry->name == name) {
                    loader.unload(entry.get());
                    break;
                }
            }

            enabledModules.erase(it);

            dataManager.releaseChannelsOf(*it);

            invalidate();
            return true;
        }
    }

    logger.error("disableModule") << "Tried to disable module " << name
                                  << ", but was not enabled.";
    return false;
}

void ExecutionManager::invalidate(){
    valid = false;
}

void ExecutionManager::validate(){
    if(!valid){
        valid = true;
        //TODO dataManager.validate()
        sort();
    }
}

void ExecutionManager::numThreads(int num) {
    m_numThreads = num;
}

void ExecutionManager::numThreadsAuto() {
    m_numThreads = std::thread::hardware_concurrency();
}

int ExecutionManager::numThreads() const {
    return m_numThreads;
}

void ExecutionManager::enabledMultithreading(bool flag) {
    m_multithreading = flag;
}

bool ExecutionManager::enabledMultithreading() const {
    return m_multithreading;
}

void ExecutionManager::printCycleList(cycleListType &clist) {
    for(const std::vector<Module*> &list : clist) {
        std::string line;

        for(Module* mod : list) {
            line += mod->getName() + " ";
        }

        logger.debug("cycleList") << line;
    }
}

void ExecutionManager::printCycleList() {
    printCycleList(cycleList);
}

void ExecutionManager::sort(){
    cycleList.clear();
    logger.debug("sort") << "No. of enabled modules: " << enabledModules.size();
    //add modules to the list
    for(std::shared_ptr<ModuleWrapper> it : enabledModules){
        std::vector<Module*> tmp;
        tmp.push_back(it->moduleInstance);
        cycleList.push_back(tmp);
    }
    sortByDataChannel();
    sortByPriority();
}

void ExecutionManager::sortByDataChannel(){
    // getChannels() returns const& -> you must use a const& here as well
    for(const std::pair<std::string, DataManager::DataChannel> &pair : dataManager.getChannels()){
        // Module* here is ok, you will make a copy of the pointer
        for(std::shared_ptr<ModuleWrapper> reader : pair.second.readers){
            // usual & here
            for(std::vector<Module*> &list: cycleList){
                Module *toAdd = list[0];
                //add all writers to the reader
                if(toAdd->getName() == reader->name){
                    for(std::shared_ptr<ModuleWrapper> writer : pair.second.writers){
                        list.push_back(writer->moduleInstance);
                    }
                }
            }
        }
    }
}

void ExecutionManager::sortByPriority(){
    // const& here again
    for(const std::pair<std::string, DataManager::DataChannel>& pair : dataManager.getChannels()){
        //sort writer-order read-order isn't needed as readers don't change the dataChannel
        //check insert is in the writers-list BEGIN
        for(std::shared_ptr<ModuleWrapper> writer1 : pair.second.writers){
            for(std::vector<Module*> &list: cycleList){
                Module* insert = list[0];
                //check insert is in the writers-list END
                if(insert->getName() == writer1->name){
                    //yes it is contained
                    for(std::shared_ptr<ModuleWrapper> writer2 : pair.second.writers){
                        //add all writers(2) with a higher priority to the list
                        if(writer2->writePriority > insert->getPriority()){
                            list.push_back(writer2->moduleInstance);
                        }
                    }
                }
            }
        }
    }
}


Profiler& ExecutionManager::profiler() {
    return m_profiler;
}

Messaging& ExecutionManager::messaging() {
    return m_messaging;
}

const ModuleList& ExecutionManager::getEnabledModules() const {
    return enabledModules;
}

void ExecutionManager::fireConfigsChangedEvent() {
    for(std::shared_ptr<ModuleWrapper> mod : enabledModules) {
        mod->moduleInstance->configsChanged();
    }
}

int ExecutionManager::cycleCounter() {
    return m_cycleCounter;
}

}  // namespace lms
