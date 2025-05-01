#include "FlowMeasure.h"

using namespace ecfmp::types;

FlowMeasure::FlowMeasure() {}

FlowMeasure::FlowMeasure(std::int64_t id, std::string ident, std::int64_t event_id, std::string reason,
                         std::chrono::utc_clock::time_point start_time, std::chrono::utc_clock::time_point end_time,
                         std::chrono::utc_clock::time_point withdrawn_at, std::list<int> notified_firs,
                         std::vector<Measure> measures, std::vector<Filter> filters)
    : id(id),
      ident(ident),
      event_id(event_id),
      reason(reason),
      start_time(start_time),
      end_time(end_time),
      withdrawn_at(withdrawn_at),
      notified_firs(notified_firs),
      measures(measures),
      filters(filters) {}

const FlowMeasure FlowMeasure::fromJson(const json& j) {
    FlowMeasure flowMeasure;

    flowMeasure.id = j.value("id", -1);
    flowMeasure.ident = j.value("ident", "");
    flowMeasure.event_id = j.value("event_id", -1);
    flowMeasure.reason = j.value("reason", "");
    flowMeasure.notified_firs = j.value("notified_firs", std::list<int>());

    if (j.contains("start_time")) {
        flowMeasure.start_time = utils::Date::isoStringToTimestamp(j.at("start_time").get<std::string>());
    }
    if (j.contains("end_time")) {
        flowMeasure.end_time = utils::Date::isoStringToTimestamp(j.at("end_time").get<std::string>());
    }
    if (j.contains("withdrawn_at")) {
        flowMeasure.withdrawn_at = utils::Date::isoStringToTimestamp(j.at("withdrawn_at").get<std::string>());
    }
    if (j.contains("measures")) {
        for (const auto& measure : j.at("measures")) {
            flowMeasure.measures.push_back(Measure::fromJson(measure));
        }
    }
    if (j.contains("filters")) {
        for (const auto& filter : j.at("filters")) {
            flowMeasure.filters.push_back(Filter::fromJson(filter));
        }
    }
    return flowMeasure;
}
