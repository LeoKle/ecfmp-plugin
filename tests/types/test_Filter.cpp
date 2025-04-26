#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "types/Filter.h"

using json = nlohmann::json;

TEST(FilterTest, TestFilterTypeFromString) {
    using namespace ecfmp::types;

    EXPECT_EQ(Filter::filterTypeFromString("ADEP"), FilterType::ADEP);
    EXPECT_EQ(Filter::filterTypeFromString("ADES"), FilterType::ADES);
    EXPECT_EQ(Filter::filterTypeFromString("level_above"), FilterType::LEVEL_ABOVE);
    EXPECT_EQ(Filter::filterTypeFromString("level_below"), FilterType::LEVEL_BELOW);
    EXPECT_EQ(Filter::filterTypeFromString("level"), FilterType::LEVEL);
    EXPECT_EQ(Filter::filterTypeFromString("member_event"), FilterType::MEMBER_EVENT);
    EXPECT_EQ(Filter::filterTypeFromString("member_not_event"), FilterType::MEMBER_NOT_EVENT);
    EXPECT_EQ(Filter::filterTypeFromString("waypoint"), FilterType::WAYPOINT);
    EXPECT_EQ(Filter::filterTypeFromString("invalid_type"), FilterType::NONE);
}

TEST(FilterTest, TestFilterFromJson) {
    using namespace ecfmp::types;

    const json adepJson = {{"type", "ADEP"}, {"value", "KATL"}};
    const auto filterAdep = Filter::fromJson(adepJson);
    EXPECT_EQ(filterAdep.type, FilterType::ADEP);
    EXPECT_EQ(std::get<std::string>(filterAdep.value), "KATL");

    const json adesJson = {{"type", "ADES"}, {"value", "KATL"}};
    const auto filterAdes = Filter::fromJson(adesJson);
    EXPECT_EQ(filterAdes.type, FilterType::ADES);
    EXPECT_EQ(std::get<std::string>(filterAdes.value), "KATL");

    const json levelAboveJson = {{"type", "level_above"}, {"value", 350}};
    const auto filterLevelAbove = Filter::fromJson(levelAboveJson);
    EXPECT_EQ(filterLevelAbove.type, FilterType::LEVEL_ABOVE);
    EXPECT_EQ(std::get<std::int64_t>(filterLevelAbove.value), 350);

    const json levelBelowJson = {{"type", "level_below"}, {"value", 240}};
    const auto filterLevelBelow = Filter::fromJson(levelBelowJson);
    EXPECT_EQ(filterLevelBelow.type, FilterType::LEVEL_BELOW);
    EXPECT_EQ(std::get<std::int64_t>(filterLevelBelow.value), 240);

    const json levelJson = {{"type", "level"}, {"value", {240, 350}}};
    const auto filterLevel = Filter::fromJson(levelJson);
    EXPECT_EQ(filterLevel.type, FilterType::LEVEL);
    EXPECT_EQ(std::get<std::vector<std::int64_t>>(filterLevel.value), std::vector<std::int64_t>({240, 350}));

    const json memberEventJson = {
        {"type", "member_event"},
        {"value", json::array({{{"event_id", 64}, {"event_vatcan", "string"}, {"event_api", nullptr}},
                               {{"event_id", 65}, {"event_vatcan", "string"}, {"event_api", nullptr}}})}};
    const auto filterMemberEvent = Filter::fromJson(memberEventJson);
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberEvent.value).size(), 2);
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberEvent.value)[0].event_id, 64);
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberEvent.value)[0].event_vatcan, "string");
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberEvent.value)[0].event_api, "null");
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberEvent.value)[1].event_id, 65);
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberEvent.value)[1].event_vatcan, "string");
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberEvent.value)[1].event_api, "null");

    const json memberNotEventJson = {
        {"type", "member_not_event"},
        {"value", json::array({{{"event_id", 64}, {"event_vatcan", "string"}, {"event_api", nullptr}},
                               {{"event_id", 65}, {"event_vatcan", "string"}, {"event_api", nullptr}}})}};
    const auto filterMemberNotEvent = Filter::fromJson(memberNotEventJson);
    EXPECT_EQ(filterMemberNotEvent.type, FilterType::MEMBER_NOT_EVENT);
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberNotEvent.value).size(), 2);
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberNotEvent.value)[0].event_id, 64);
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberNotEvent.value)[0].event_vatcan, "string");
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberNotEvent.value)[0].event_api, "null");
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberNotEvent.value)[1].event_id, 65);
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberNotEvent.value)[1].event_vatcan, "string");
    EXPECT_EQ(std::get<std::vector<EventData>>(filterMemberNotEvent.value)[1].event_api, "null");

    const json waypointJson = {{"type", "waypoint"}, {"value", {"DIXAT", "ADEMI"}}};
    const auto filterWaypoint = Filter::fromJson(waypointJson);
    EXPECT_EQ(filterWaypoint.type, FilterType::WAYPOINT);
    EXPECT_EQ(std::get<std::vector<std::string>>(filterWaypoint.value), std::vector<std::string>({"DIXAT", "ADEMI"}));
}