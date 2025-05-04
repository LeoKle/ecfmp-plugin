#include "Filter.h"

using namespace ecfmp::types;

Filter::Filter() : type(FilterType::NONE), value(std::int64_t(0)) {}

const Filter Filter::fromJson(const json& j) {
    Filter filter;
    if (j.contains("type")) {
        filter.type = filterTypeFromString(j.at("type").get<std::string>());
    }
    if (j.contains("value")) {
        switch (filter.type) {
            case FilterType::ADEP:
            case FilterType::ADES:
                filter.value = j.at("value").get<std::vector<std::string>>();
                break;
            case FilterType::LEVEL_ABOVE:
            case FilterType::LEVEL_BELOW:
                filter.value = j.at("value").get<std::int64_t>();
                break;
            case FilterType::LEVEL:
                filter.value = j.at("value").get<std::vector<std::int64_t>>();
                break;
            case FilterType::MEMBER_EVENT:
            case FilterType::MEMBER_NOT_EVENT: {
                auto events = std::vector<EventData>();
                for (const auto& event : j.at("value")) {
                    events.push_back(EventData::fromJson(event));
                }
                filter.value = events;
                break;
            }
            case FilterType::WAYPOINT:
                filter.value = j.at("value").get<std::vector<std::string>>();
                break;
            default:
                break;
        }
    }
    return filter;
}

const FilterType Filter::filterTypeFromString(const std::string& str) {
    static const std::unordered_map<std::string, FilterType> mapping = {
        {"ADEP", FilterType::ADEP},
        {"ADES", FilterType::ADES},
        {"level_above", FilterType::LEVEL_ABOVE},
        {"level_below", FilterType::LEVEL_BELOW},
        {"level", FilterType::LEVEL},
        {"member_event", FilterType::MEMBER_EVENT},
        {"member_not_event", FilterType::MEMBER_NOT_EVENT},
        {"waypoint", FilterType::WAYPOINT}};

    auto it = mapping.find(str);
    if (it != mapping.end()) {
        return it->second;
    } else {
        return FilterType::NONE;
    }
}