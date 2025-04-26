#include "Measure.h"

using namespace ecfmp::types;

Measure::Measure() : type(MeasureType::NONE), value(int64_t(0)) {}

const Measure Measure::fromJson(const json& j) {
    Measure measure;
    if (j.contains("type")) {
        measure.type = measureTypeFromString(j.at("type").get<std::string>());
    }
    if (j.contains("value")) {
        switch (measure.type) {
            case MeasureType::MDI:
            case MeasureType::ADI:
            case MeasureType::PER_HOUR:
            case MeasureType::MIT:
            case MeasureType::MAX_IAS:
            case MeasureType::MAX_MACH:
            case MeasureType::IAS_REDUCTION:
            case MeasureType::MACH_REDUCTION:
                measure.value = j.at("value").get<int64_t>();
                break;
            case MeasureType::PROHIBIT:
            case MeasureType::GROUND_STOP:
                break;
            case MeasureType::MANDATORY_ROUTE:
                measure.value = j.at("value").get<std::vector<std::string>>();
                break;
            default:
                break;
        }
    }
    return measure;
}

const MeasureType Measure::measureTypeFromString(const std::string& str) {
    static const std::unordered_map<std::string, MeasureType> mapping = {
        {"minimum_departure_interval", MeasureType::MDI},
        {"average_departure_interval", MeasureType::ADI},
        {"per_hour", MeasureType::PER_HOUR},
        {"miles_in_trail", MeasureType::MIT},
        {"max_ias", MeasureType::MAX_IAS},
        {"max_mach", MeasureType::MAX_MACH},
        {"ias_reduction", MeasureType::IAS_REDUCTION},
        {"mach_reduction", MeasureType::MACH_REDUCTION},
        {"prohibit", MeasureType::PROHIBIT},
        {"ground_stop", MeasureType::GROUND_STOP},
        {"mandatory_route", MeasureType::MANDATORY_ROUTE}};

    auto it = mapping.find(str);
    if (it != mapping.end()) {
        return it->second;
    } else {
        return MeasureType::NONE;
    }
}