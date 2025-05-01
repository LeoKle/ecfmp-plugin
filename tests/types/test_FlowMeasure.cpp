#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "types/Filter.h"
#include "types/FlowMeasure.h"
#include "types/Measure.h"
#include "utils/Date.h"

using json = nlohmann::json;

using namespace ecfmp::types;

class FlowMeasureTest : public ::testing::Test {
   protected:
    json testJson;

    void SetUp() override {
        testJson = {{"id", 123},
                    {"ident", "test_ident"},
                    {"event_id", 456},
                    {"reason", "test_reason"},
                    {"start_time", "2025-05-01T12:00:00Z"},
                    {"end_time", "2025-05-02T12:00:00Z"},
                    {"withdrawn_at", "2025-05-03T12:00:00Z"},
                    {"notified_firs", {1, 2, 3}},
                    {"measures", {}},
                    {"filters", {}}};
    }
};

TEST_F(FlowMeasureTest, fromJson_ParsesCorrectly) {
    FlowMeasure fm = FlowMeasure::fromJson(testJson);

    EXPECT_EQ(fm.id, 123);
    EXPECT_EQ(fm.ident, "test_ident");
    EXPECT_EQ(fm.event_id, 456);
    EXPECT_EQ(fm.reason, "test_reason");

    EXPECT_EQ(fm.start_time, utils::Date::isoStringToTimestamp("2025-05-01T12:00:00Z"));
    EXPECT_EQ(fm.end_time, utils::Date::isoStringToTimestamp("2025-05-02T12:00:00Z"));
    EXPECT_EQ(fm.withdrawn_at, utils::Date::isoStringToTimestamp("2025-05-03T12:00:00Z"));

    std::list<int> expectedNotifiedFirs = {1, 2, 3};
    EXPECT_EQ(fm.notified_firs, expectedNotifiedFirs);

    EXPECT_TRUE(fm.measures.empty());
    EXPECT_TRUE(fm.filters.empty());
}

TEST_F(FlowMeasureTest, fromJson_MissingFieldsUsesDefaults) {
    testJson.erase("start_time");
    testJson.erase("end_time");
    testJson.erase("withdrawn_at");

    FlowMeasure fm = FlowMeasure::fromJson(testJson);

    EXPECT_EQ(fm.start_time, std::chrono::utc_clock::time_point(utils::Date::defaultTime));
    EXPECT_EQ(fm.end_time, std::chrono::utc_clock::time_point(utils::Date::defaultTime));
    EXPECT_EQ(fm.withdrawn_at, std::chrono::utc_clock::time_point(utils::Date::defaultTime));
}

TEST_F(FlowMeasureTest, fromJson_WithFilters) {
    testJson.erase("filters");

    nlohmann::json filtersArray = {{{"type", "ADEP"}, {"value", "KATL"}}, {{"type", "ADES"}, {"value", "KATL"}}};
    testJson["filters"] = filtersArray;

    FlowMeasure fm = FlowMeasure::fromJson(testJson);

    EXPECT_EQ(fm.filters.size(), 2);
    EXPECT_EQ(fm.filters[0].type, FilterType::ADEP);
    EXPECT_EQ(std::get<std::string>(fm.filters[0].value), "KATL");

    EXPECT_EQ(fm.filters[1].type, FilterType::ADES);
    EXPECT_EQ(std::get<std::string>(fm.filters[1].value), "KATL");
}

TEST_F(FlowMeasureTest, fromJson_WithMeasures) {
    testJson.erase("measures");

    nlohmann::json measuresArray = {{{"type", "minimum_departure_interval"}, {"value", 10}},
                                    {{"type", "average_departure_interval"}, {"value", 20}}};
    testJson["measures"] = measuresArray;

    FlowMeasure fm = FlowMeasure::fromJson(testJson);

    EXPECT_EQ(fm.measures.size(), 2);
    EXPECT_EQ(fm.measures[0].type, MeasureType::MDI);
    EXPECT_EQ(std::get<int64_t>(fm.measures[0].value), 10);

    EXPECT_EQ(fm.measures[1].type, MeasureType::ADI);
    EXPECT_EQ(std::get<int64_t>(fm.measures[1].value), 20);
}