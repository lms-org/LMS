#include "lms/logging/level.h"
#include "../internal/colors.h"

namespace lms {
namespace logging {

std::string levelName(Level lvl) {
    switch (lvl) {
    case Level::ALL:
        return "ALL";
    case Level::PROFILE:
        return "PROFILE";
    case Level::DEBUG:
        return "DEBUG";
    case Level::INFO:
        return "INFO ";
    case Level::WARN:
        return "WARN ";
    case Level::ERROR:
        return "ERROR";
    case Level::OFF:
        return "OFF";
    }
    return "?";
}

bool levelFromName(const std::string &name, Level &level) {
    if (name == "ALL" || name == "all")
        level = Level::ALL;
    else if (name == "DEBUG" || name == "debug")
        level = Level::DEBUG;
    else if (name == "INFO" || name == "info")
        level = Level::INFO;
    else if (name == "WARN" || name == "warn")
        level = Level::WARN;
    else if (name == "ERROR" || name == "error")
        level = Level::ERROR;
    else if (name == "OFF" || name == "off")
        level = Level::OFF;
    else
        return false;

    return true;
}

std::string levelColor(Level lvl) {
    switch (lvl) {
    case Level::DEBUG:
        return lms::internal::COLOR_GREEN;
    case Level::INFO:
        return lms::internal::COLOR_BLUE;
    case Level::WARN:
        return lms::internal::COLOR_YELLOW;
    case Level::ERROR:
        return lms::internal::COLOR_RED;
    default:
        return lms::internal::COLOR_WHITE; // ALL, OFF
    }
}

} // namespace logging
} // namespace lms
