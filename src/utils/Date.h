#pragma once

#include <chrono>
#include <string>

namespace utils {
class Date {
   public:
    Date() = delete;

    static constexpr std::chrono::utc_clock::time_point defaultTime =
        std::chrono::utc_clock::time_point(std::chrono::milliseconds(-1));

    static std::string timestampToIsoString(const std::chrono::utc_clock::time_point &timepoint) {
        if (timepoint.time_since_epoch().count() >= 0) {
            std::stringstream stream;
            stream << std::format("{0:%FT%T}", timepoint);
            auto timestamp = stream.str();
            timestamp = timestamp.substr(0, timestamp.length() - 4) + "Z";
            return timestamp;
        } else {
            return "1969-12-31T23:59:59.999Z";
        }
    }

    static std::chrono::utc_clock::time_point isoStringToTimestamp(const std::string &timestamp) {
        std::chrono::utc_clock::time_point timepoint;
        std::stringstream stream;

        stream << timestamp.substr(0, timestamp.length() - 1);
        std::chrono::from_stream(stream, "%FT%T", timepoint);

        return timepoint;
    }
};
}  // namespace utils