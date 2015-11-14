#ifndef LMS_DATA_CHANNEL_H
#define LMS_DATA_CHANNEL_H
#include <cstring>
#include <vector>
#include <memory>
#include <algorithm>
#include "lms/logger.h"
#include "lms/serializable.h"
#include "data_channel_internal.h"

namespace lms {
class Runtime; //circle dependency
struct ModuleWrapper;

template<typename T>
class DataChannel {
public:
    DataChannel(std::shared_ptr<DataChannelInternal> internal) :
        m_internal(internal) {}
public: //TODO
    std::shared_ptr<DataChannelInternal> m_internal;
public:

    std::string name() const{
        return m_internal->name;
    }


    /**
     * return returns SUBTYPE if the current object is a subtype of the given one
     */
    template<typename L> TypeResult checkType(){
        return m_internal->main->checkType<L>();
    }
    template<typename L> bool castableTo(){
        TypeResult r = checkType<L>();
        return r == TypeResult::SAME || r == TypeResult::SUBTYPE;
    }
    bool serialize(std::ostream &os) {
        // if we would use dynamic_cast here, we could remove the serializable
        // flag of data channels, but that is not necessarily faster or better

        if(m_internal->main && m_internal->main->isSerializable()) {
            const Serializable *data = static_cast<Serializable*>(m_internal->main->get());
            data->lmsSerialize(os);
            return true;
        } else {
            return false;
        }
    }
    /**
     * @brief getVoid used if you initialised the DataChannel with lms::Void
     * @return void* of the contained object
     */
    void* getVoid(){
        return m_internal->main->get();
    }
    //Util-method
    template <typename A, bool suppInher>
    struct InheritanceCallerGet;

    template <typename A>
    struct InheritanceCallerGet<A, false> {
        static T* call(DataChannel<A> *obj) {
            return static_cast<T*>(obj->m_internal->main->get());
        }
    };

    template <typename A>
    struct InheritanceCallerGet<A, true> {
        static T* call (DataChannel<A> *obj) {
            return static_cast<T*>(obj->m_internal->main->getInheritance());
        }
    };

    /**
     * @brief get returns the contained object, if you have a lms::Void type, use getVoid()
     * @return
     */
    virtual T* get() {
        if(std::is_same<T, Any>::value){
            return nullptr;
        }
        return InheritanceCallerGet<T,std::is_base_of<Inheritance,T>::value>::call(this);

    }
};

template<typename T>
class ReadDataChannel : public DataChannel<T> {
public:
    ReadDataChannel() : DataChannel<T>(nullptr) {}

    ReadDataChannel(std::shared_ptr<DataChannelInternal> internal) :
        DataChannel<T>(internal) {}
    /**
     * @brief get returns the contained object, if you have a lms::Void type, use getVoid()
     * @return
     */
    /*
    const T* get() {
        //Handle lms::Void pointer
        if(std::is_same<T, Void>::value){
            return nullptr;
        }
        return static_cast<const T*>(this->m_internal->main->get());

        // TODO buffer
        if(this->m_internal->buffered()){
            if(this->m_internal->m_buffer.size() > 0)
                return this->m_internal->m_buffer[this->m_internal->m_buffer.size() -1];
            else
                return nullptr;
        }else{

        }
    }
    */
    const T* operator ->() {
        return this->get();
    }

    const T& operator *() {
        return *this->get();
    }
};

template<typename T>
class WriteDataChannel : public DataChannel<T> {
public:
    WriteDataChannel(std::shared_ptr<DataChannelInternal> internal) :
        DataChannel<T>(internal) {}

    WriteDataChannel() : DataChannel<T>(nullptr) {}

    T* operator ->(){
        //m_cycle = maintainer->cycleCount();
        return this->get();
    }

    T& operator *() {
        return *this->get();
    }

    bool deserialize(std::istream &is) {
        if(this->m_internal->main && this->m_internal->main->isSerializable()) {
            Serializable *data = static_cast<Serializable*>(this->m_internal->main->get());
            data->lmsDeserialize(is);
            return true;
        } else {
            return false;
        }
    }
};

}  //namespace lms

#endif //LMS_DATA_CHANNEL_H
