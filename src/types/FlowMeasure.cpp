#include "FlowMeasure.h"

using namespace ecfmp::types;

FlowMeasure::FlowMeasure() : event_id(-1) {}

const FlowMeasure FlowMeasure::fromJson(const json& j) {
    FlowMeasure flowMeasure;

    flowMeasure.id = j.value("id", -1);
    flowMeasure.ident = j.value("ident", "");

    if (j.contains("event_id") && !j.at("event_id").is_null()) {
        flowMeasure.event_id = j.at("event_id").get<std::int64_t>();
    }

    flowMeasure.reason = j.value("reason", "");
    flowMeasure.notified_firs = j.value("notified_flight_information_regions", std::list<int>());

    if (j.contains("starttime") && !j.at("starttime").is_null()) {
        flowMeasure.start_time = utils::Date::isoStringToTimestamp(j.at("starttime").get<std::string>());
    }
    if (j.contains("endtime") && !j.at("endtime").is_null()) {
        flowMeasure.end_time = utils::Date::isoStringToTimestamp(j.at("endtime").get<std::string>());
    }
    if (j.contains("withdrawn_at") && !j.at("withdrawn_at").is_null()) {
        flowMeasure.withdrawn_at = utils::Date::isoStringToTimestamp(j.at("withdrawn_at").get<std::string>());
    }
    if (j.contains("measure")) {
        const auto measure = j.at("measure");
        flowMeasure.measure = Measure::fromJson(measure);
    }
    if (j.contains("filters")) {
        for (const auto& filter : j.at("filters")) {
            flowMeasure.filters.push_back(Filter::fromJson(filter));
        }
    }
    return flowMeasure;
}
