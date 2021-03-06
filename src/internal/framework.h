#pragma once

#include <string>
#include <vector>

#include "lms/datamanager.h"
#include "signalhandler.h"
#include "argumenthandler.h"
#include "executionmanager.h"
#include "lms/logger.h"
#include "clock.h"
#include "pugixml.hpp"
#include "file_monitor.h"
#include "debug_server.h"
#include "signalhandler.h"
#include "messages.pb.h"

namespace lms {
namespace internal {

/**
 * @brief Main entry point into the lightweight module system.
 *
 * Create an object of this class and you will start the framwork.
 */
class Framework : public SignalHandler::Listener {
public:
    /**
     * @brief Instantiate the framework, initiate datamanager and
     * execution manager and start the main loop.
     *
     * @param arguments parsed command line arguments
     */
    Framework(const std::string &mainConfigFilePath);

    /**
     * @brief Destroy execution manager.
     */
    ~Framework();

    std::shared_ptr<Service> getService(std::string const &name);

    bool isDebug() const;
    void setDebug(bool debug);

    void addSearchPath(const std::string &path);
    void addFlag(const std::string &flag);

    void enableLoad(const std::string &path);
    void enableSave(const std::string &path);

    std::string loadLogObject(std::string const &name, bool isDir);
    std::string saveLogObject(std::string const &name, bool isDir);
    bool isEnableLoad() const;
    bool isEnableSave() const;
    std::string loadPath() const;

    /**
     * @brief Synchronously execute a single cycle of this runtime.
     * @return true if cycle got executed, false if runtime is paused
     */
    bool cycle();

    void start();
    void stop();

    DataManager& dataManager();
    ExecutionManager &executionManager();

    virtual void signal(int signal);

    void printDAG();

    void startCommunicationThread(int sock);

    void loadRecordings(const std::string &absPath, const std::vector<std::string> &channels);
private:
    bool updateSystem(const RuntimeInfo &info);
    void printOverview();
    void printModuleChannelGraph();
    void shutdown();

    ExecutionManager m_executionManager;
    DataManager m_dataManager;
    Clock m_clock;

    logging::Logger logger;

    Loader m_loader;

    extra::FileMonitor configMonitor;

    std::string mainConfigFilePath;

    bool m_running;
    bool is_debug;

    std::map<std::string, std::shared_ptr<Service>> services;
    std::map<std::string, std::shared_ptr<Module>> modules;

    std::string configPath;
    std::vector<std::string> flags;

    static constexpr std::uint32_t MODE = 0775;
    std::string m_loadLogPath;
    std::string m_saveLogPath;
    bool m_isEnableLoad = false;
    bool m_isEnableSave = false;

    std::thread m_communicationThread;
    std::mutex m_queueMutex;
    std::list<lms::Request> m_queue;

    // recording
    enum RecordingState {
        NONE, LOAD, SAVE
    };
    std::mutex m_recordingMutex;
    RecordingState m_recordingState = NONE;
    bool m_firstRecordSavingCycle = false;
    std::map<std::string, std::fstream> m_recordingStreams;
    // modules that write into channels that were serialized
    std::set<std::string> m_ignoreModules;
    std::string m_absLoadPath;
    bool m_firstRecordLoadingCycle = false;
    void initChannelTypes();
};

} // namespace internal
} // namespace lms
