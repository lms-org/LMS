#ifndef LMS_MODULE_H
#define LMS_MODULE_H

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "service.h"
#include "datamanager.h"
#include "config.h"
#include "deprecated.h"
#include "lms/definitions.h"
#include "service_handle.h"
#include "interface.h"
#include "life_cycle.h"

namespace lms {

class Messaging;
namespace internal {
class Framework;
class ModuleInfo;
}

/**
 * @brief Abstract super class for dynamic loadable modules
 * with a guaranteed lifecycle.
 *
 * Lifecycle:
 * - initialize() - called once after module loading
 * - cycle() - can be called any number of times
 * - deinitialize() - called once before module unloading
 */
class Module : public LifeCycle {
public:
    Module();
    virtual ~Module();

    // Disallow copying
    Module(Module const&) = delete;
    Module& operator=(Module const&) = delete;

    /**
     * @brief Name of the module itself.
     *
     * Can be called inside a module's initialize, cycle or
     * deinitialize method.
     *
     * @return name of the loaded module
     */
    std::string getName() const;

    /**
     * @brief Called by the framework itself at module-creation.
     *
     * Do not call this inside a module!
     */
    bool initBase(const internal::ModuleInfo &info, internal::Framework *fw);

    /**
     * @brief Check if this module is executed on the main thread or another
     * thread.
     * @return ONLY_MAIN_THREAD or NEVER_MAIN_THREAD
     */
    bool isMainThread() const;

    /**
     * @brief Informs a module of the start of its
     * lifecycle.
     *
     * Modules should request configs and data channels during
     * execution of this method. Modules should also
     * also allocate memory and open files here.
     *
     * This method will be called only once and before
     * every other lifecycle method.
     *
     * Must be overridden by modules.
     *
     * Returning false will prohibit the module from being
     * loaded. cycle and deinitialize will never be called in
     * this case.
     *
     * @return true if initialization was succesful, otherwise false
     */
    virtual bool init() override;

    /**
     * @brief Deprecated alias for init().
     * @return true if initialization was successful, otherwise false
     */
    virtual bool initialize();

    /**
     * @brief Informs a module that it should now read or write to
     * data channels and/or start computing something.
     *
     * Modules can read from or write to data channels.
     *
     * The cycle method can be called never, once or for any other
     * random number of times. The cycle method is guaranteed to be called
     * after initialize and before deinitialize was called.
     *
     * Must be overridden by modules.
     *
     * @return true if cycling was succesul was succesful, otherwise false
     */
    virtual bool cycle() = 0;

    /**
     * @brief Informs a module of the end of its
     * lifecycle.
     *
     * Modules should destroy any allocated memory, file descriptors
     * and call delete on any pointers that were created with
     * new in initialize.
     *
     * This method will be called only once and after
     * every other lifecycle method. This method is
     * guaranteed to be called after initialize() returned
     * true. This method will be never called before initialize().
     *
     * Must be overridden by a module.
     */
    virtual void destroy() override;

    /**
     * @brief Deprecated alias for destroy.
     * @return ignored
     */
    virtual bool deinitialize();

    /**
     * @brief This method gets called whenever a config changed during
     *execution.
     *
     * A config is usually only changed when the config monitor found changes
     * in the config files.
     *
     * NOTE: This method can be called even if no config files accessed by this
     * module were changed.
     */
    virtual void configsChanged() override;

    /**
     * @brief Return the current number of the cycle counter which is
     * incremented after each cycle by 1.
     * @return cycle number
     */
    int cycleCounter();

protected:
    /**
     * @brief Returns a handle to a service. The service is locked during the
     * handle's lifetime and no other process may call methods and access
     * properties of the service.
     *
     * Usage:
     * ~~~~~{.cpp}
     * {
     *   ServiceHandle<MyService> service = getService<MyService>("my_service");
     *   service->doSomething();
     *   // unlocks automatically
     * }
     * ~~~~~
     */
    template <class T> ServiceHandle<T> getService(std::string const &name) {
        auto service = _getService(name);

        if (service /*&& wrapper->checkHashCode(typeid(T).hash_code())*/) {
            // TODO type check
            return ServiceHandle<T>(service);
        } else {
            // return invalid handle
            return ServiceHandle<T>();
        }
    }

    /**
     * @brief Returns the service instance of the given name if available.
     * This does not lock the service and is therefore not thread-safe.
     */
    template <class T> T *getUnsafeService(std::string const &name) {
        auto service = _getService(name);

        if (service) {
            return static_cast<T *>(service.get());
        } else {
            // TODO throw std::system_error("Service not installed: " + name);
            return nullptr;
        }
    }

    /**
     * @brief Returns the messaging service.
     *
     * Send or receive messages between different modules
     * and the core framework.
     */
    Messaging *messaging() const;

    /**
     * @brief Check if --enable-save was given on the command line.
     * @return true if set, false otherwise
     */
    bool isEnableSave() const;

    /**
     * @brief Check if --enable-load was given on the command line.
     * @return true if set, false otherwise
     */
    bool isEnableLoad() const;

    /**
     * @brief Return the path to a log file with the given name.
     *
     * The file will not be created but its parent directories will be if
     * --enable-save was given on the command line.
     *
     * Do not use if isEnableSave() returns false.
     *
     * @param name file name
     * @return absolute path to a file
     */
    std::string saveLogFile(std::string const &name);

    /**
     * @brief Return the path to a log file with the given name.
     *
     * The file will not be created.
     *
     * Do not use if isEnableLoad() returns false;
     *
     * @param name
     * @return
     */
    std::string loadLogFile(std::string const &name);

    /**
     * @brief Return the path to a log directory with a given name.
     *
     * The directory (and all parent directories) will be created if
     * --enable-save was given on the command line.
     *
     * Do not use if isEnableSave() returns false.
     *
     * @param name directory name
     * @return absolute path to a directory with trailing slash
     */
    std::string saveLogDir(std::string const &name);

    /**
     * @brief Return the path to a log directory with a given name.
     *
     * The directory will not be created.
     *
     * Do not use if isEnableLoad() returns false.
     *
     * @param name
     * @return
     */
    std::string loadLogDir(std::string const &name);

    /**
     * @brief A logger instance. Can be used in initialize, cycle
     * and deinitialize to log debugging information.
     */
    logging::Logger logger;

    /**
     * @brief Return a read-only config of the given name.
     * @param name config's name
     * @return module config
     */
    const Config &config(const std::string &name = "default");

    /**
     * @brief Check if a config of the given name was loaded.
     * @param name config's name
     * @return true if config is loaded, false otherwise
     */
    bool hasConfig(const std::string &name = "default");

    /**
     * @brief Read a data channel and return a corresponding handle.
     * Should be called in initialize() but can be called in cycle() as well.
     * The invokation of this method may change the module execution order.
     * @param name channel name
     * @return data channel handle
     */
    template <typename T>
    ReadDataChannel<T> readChannel(const std::string &name) {
        gainReadAccess(name);
        return datamanager().readChannel<T>(mapChannel(name));
    }

    /**
     * @brief Write a data channel and return a corresponding handle.
     * Should be called in initialize() but can be called cycle() as well.
     * The invokation of this method may change the module execution order.
     * @param name channel name
     * @return data channel handle
     */
    template <typename T>
    WriteDataChannel<T> writeChannel(const std::string &name) {
        gainWriteAccess(name);
        return datamanager().writeChannel<T>(mapChannel(name));
    }

    /**
     * @brief Check if the channel exists and there is atleast module reading from it
     * @param channelName channel's name
     * @return true if there is one reader of this channel
     */
    bool isChannelInUse(const std::string &channelName) const;

    /**
     * @brief Pause a running runtime or do nothing if already pausing.
     *
     * @return true if pausing was successful, false if runtime was not found
     */
    bool pauseRuntime(std::string const &name);

    /**
     * @brief Pause the module's own runtime.
     */
    void pauseRuntime();

    /**
     * @brief Resume a paused runtime or do nothing if already running.
     *
     * @return true if resuming was successful, false if runtime was not found.
     */
    bool resumeRuntime(std::string const &name, bool reset = false);

    /**
     * @brief Stop and shutdown runtime after the current cycle.
     * @param status Return status to master server and to all attached clients.
     */
    void exitRuntime(int status = 0);

private:
    std::shared_ptr<Service>
    _getService(std::string const &name);

    struct Private;
    Private *dptr;
    inline Private *dfunc() { return dptr; }
    inline const Private *dfunc() const { return dptr; }

    std::string mapChannel(const std::string &channelName);
    void gainReadAccess(const std::string &channelName);
    void gainWriteAccess(const std::string &channelName);

    DataManager &datamanager();
};

} // namespace lms

#endif /* LMS_MODULE_H */
