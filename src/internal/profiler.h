#pragma once

#include <map>
#include <string>

#include "lms/time.h"
#include "lms/logging/trace.h"

namespace lms {
namespace internal {

class Profiler {
public:
    void addBegin(const std::string &tag, lms::Time timestamp);
    void addEnd(const std::string &tag, lms::Time timestamp);
    void getOverview(std::map<std::string, logging::Trace<double>> &result) const;
    void reset();
private:
    std::map<std::string, logging::Trace<double>> measurements;
};

}
}
