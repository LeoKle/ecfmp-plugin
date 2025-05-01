#pragma once

#include <cstdint>
#include <nlohmann/json.hpp>
#include <string>
#include <variant>
#include <vector>

using json = nlohmann::json;

namespace ecfmp::types {
enum class MeasureType {
    NONE,
    MDI,
    ADI,
    PER_HOUR,
    MIT,
    MAX_IAS,
    MAX_MACH,
    IAS_REDUCTION,
    MACH_REDUCTION,
    PROHIBIT,
    GROUND_STOP,
    MANDATORY_ROUTE
};

class Measure {
   public:
    MeasureType type;
    std::variant<int64_t, std::vector<std::string>> value;

    Measure();

    static const Measure fromJson(const json& j);
    static const MeasureType measureTypeFromString(const std::string& str);
};
}  // namespace ecfmp::types