#include <cstdint>
#include <nlohmann/json.hpp>
#include <string>
#include <variant>
#include <vector>

using json = nlohmann::json;

namespace ecfmp::types {
enum class FilterType { NONE, ADEP, ADES, LEVEL_ABOVE, LEVEL_BELOW, LEVEL, MEMBER_EVENT, MEMBER_NOT_EVENT, WAYPOINT };

struct EventData {
    int event_id;
    std::string event_vatcan;
    std::string event_api;  // according to API docs, currently always null

    static EventData fromJson(const json& j) {
        return {j.at("event_id").get<int>(), j.at("event_vatcan").get<std::string>(), "null"};
    }
};

class Filter {
   public:
    FilterType type;
    std::variant<std::int64_t, std::string, std::vector<std::int64_t>, std::vector<std::string>,
                 std::vector<struct EventData>>
        value;

    Filter();

    static const Filter fromJson(const json& j);
    static const FilterType filterTypeFromString(const std::string& str);
};
}  // namespace ecfmp::types