#pragma once

#include <chrono>
#include <cstdint>
#include <list>
#include <string>
#include <vector>

#include "Filter.h"
#include "Measure.h"
#include "utils/Date.h"

namespace ecfmp::types {
class FlowMeasure {
   public:
    std::int64_t id;
    std::string ident;
    std::int64_t event_id;
    std::string reason;

    std::chrono::utc_clock::time_point start_time = utils::Date::defaultTime;
    std::chrono::utc_clock::time_point end_time = utils::Date::defaultTime;
    std::chrono::utc_clock::time_point withdrawn_at = utils::Date::defaultTime;
    std::list<int> notified_firs;

    Measure measure;
    std::vector<Filter> filters;

    FlowMeasure();

    static const FlowMeasure fromJson(const json& j);
};
}  // namespace ecfmp::types