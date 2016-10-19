#pragma once

#include <mutex>

#include "lms/logging/sink.h"
#include "lms/logging/event.h"
#include "protobuf_socket.h"

namespace lms {
namespace internal {

class ProtobufSink : public lms::logging::Sink {
public:
    ProtobufSink(int socket);

    ~ProtobufSink() {}

    void sink(const lms::logging::Event &message) override;
private:
    lms::internal::ProtobufSocket socket;
    std::mutex mtx;
};

}  // namespace internal
}  // namespace lms