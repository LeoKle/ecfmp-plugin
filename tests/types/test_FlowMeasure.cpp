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
                    {"starttime", "2025-05-01T12:00:00Z"},
                    {"endtime", "2025-05-02T12:00:00Z"},
                    {"withdrawn_at", "2025-05-03T12:00:00Z"},
                    {"notified_flight_information_regions", {1, 2, 3}},
                    {"measures", {}},
                    {"filters", {}}};
    }
};

TEST_F(FlowMeasureTest, fromApi) {
    testJson = R"(
            {
                "id": 1669,
                "ident": "LSAS04B",
                "event_id": null,
                "reason": "Weather and airport capacity.",
                "starttime": "2025-05-04T17:30:00Z",
                "endtime": "2025-05-04T20:00:00Z",
                "measure": {
                    "type": "minimum_departure_interval",
                    "value": 240
                },
                "filters": [
                    {
                        "type": "ADEP",
                        "value": ["LOWS"]
                    },
                    {
                        "type": "ADES",
                        "value": ["LSZB"]
                    }
                ],
                "notified_flight_information_regions": [48],
                "withdrawn_at": null
            }
        )"_json;

    FlowMeasure fm = FlowMeasure::fromJson(testJson);

    EXPECT_EQ(fm.id, 1669) << "ID mismatch";
    EXPECT_EQ(fm.ident, "LSAS04B") << "Ident mismatch";
    EXPECT_EQ(fm.event_id, -1) << "Event ID mismatch";
    EXPECT_EQ(fm.reason, "Weather and airport capacity.") << "Reason mismatch";

    EXPECT_EQ(fm.start_time, utils::Date::isoStringToTimestamp("2025-05-04T17:30:00Z")) << "Start time mismatch";
    EXPECT_EQ(fm.end_time, utils::Date::isoStringToTimestamp("2025-05-04T20:00:00Z")) << "End time mismatch";
    EXPECT_EQ(fm.withdrawn_at, std::chrono::utc_clock::time_point(utils::Date::defaultTime))
        << "Withdrawn time mismatch";

    EXPECT_EQ(fm.notified_firs.size(), 1) << "Notified FIRs size mismatch";
    EXPECT_EQ(fm.notified_firs.front(), 48) << "Notified FIRs value mismatch";

    EXPECT_EQ(fm.filters.size(), 2) << "Filters size mismatch";
    EXPECT_EQ(fm.filters[0].type, FilterType::ADEP) << "Filter type mismatch";
    EXPECT_EQ(std::get<std::vector<std::string>>(fm.filters[0].value)[0], "LOWS") << "Filter value mismatch";
    EXPECT_EQ(fm.filters[1].type, FilterType::ADES) << "Filter type mismatch";
    EXPECT_EQ(std::get<std::vector<std::string>>(fm.filters[1].value)[0], "LSZB") << "Filter value mismatch";

    EXPECT_EQ(fm.measure.type, MeasureType::MDI) << "Measure type mismatch";
    EXPECT_EQ(std::get<int64_t>(fm.measure.value), 240) << "Measure value mismatch";
}

TEST_F(FlowMeasureTest, fromJson_ParsesCorrectly) {
    FlowMeasure fm = FlowMeasure::fromJson(testJson);

    EXPECT_EQ(fm.id, 123) << "ID mismatch";
    EXPECT_EQ(fm.ident, "test_ident") << "Ident mismatch";
    EXPECT_EQ(fm.event_id, 456) << "Event ID mismatch";
    EXPECT_EQ(fm.reason, "test_reason") << "Reason mismatch";

    EXPECT_EQ(fm.start_time, utils::Date::isoStringToTimestamp("2025-05-01T12:00:00Z")) << "Start time mismatch";
    EXPECT_EQ(fm.end_time, utils::Date::isoStringToTimestamp("2025-05-02T12:00:00Z")) << "End time mismatch";
    EXPECT_EQ(fm.withdrawn_at, utils::Date::isoStringToTimestamp("2025-05-03T12:00:00Z")) << "Withdrawn time mismatch";

    std::list<int> expectedNotifiedFirs = {1, 2, 3};
    EXPECT_EQ(fm.notified_firs, expectedNotifiedFirs) << "Notified FIRs mismatch";

    EXPECT_EQ(fm.measure.type, MeasureType::NONE) << "Measure type mismatch";
    EXPECT_EQ(std::get<int64_t>(fm.measure.value), 0) << "Measure value index mismatch";

    EXPECT_TRUE(fm.filters.empty()) << "Filters should be empty";
}

TEST_F(FlowMeasureTest, fromJson_MissingFieldsUsesDefaults) {
    testJson.erase("starttime");
    testJson.erase("endtime");
    testJson.erase("withdrawn_at");

    FlowMeasure fm = FlowMeasure::fromJson(testJson);

    EXPECT_EQ(fm.start_time, std::chrono::utc_clock::time_point(utils::Date::defaultTime));
    EXPECT_EQ(fm.end_time, std::chrono::utc_clock::time_point(utils::Date::defaultTime));
    EXPECT_EQ(fm.withdrawn_at, std::chrono::utc_clock::time_point(utils::Date::defaultTime));
}

TEST_F(FlowMeasureTest, fromJson_WithFilters) {
    testJson.erase("filters");

    nlohmann::json filtersArray = {{{"type", "ADEP"}, {"value", {"KATL"}}}, {{"type", "ADES"}, {"value", {"KATL"}}}};
    testJson["filters"] = filtersArray;

    FlowMeasure fm = FlowMeasure::fromJson(testJson);

    EXPECT_EQ(fm.filters.size(), 2);
    EXPECT_EQ(fm.filters[0].type, FilterType::ADEP);

    EXPECT_EQ(std::get<std::vector<std::string>>(fm.filters[0].value)[0], "KATL");

    EXPECT_EQ(fm.filters[1].type, FilterType::ADES);
    EXPECT_EQ(std::get<std::vector<std::string>>(fm.filters[1].value)[0], "KATL");
}

TEST_F(FlowMeasureTest, fromJson_WithMeasures) {
    testJson.erase("measure");

    nlohmann::json measureJson = {{"type", "minimum_departure_interval"}, {"value", 10}};
    testJson["measure"] = measureJson;

    FlowMeasure fm = FlowMeasure::fromJson(testJson);

    EXPECT_EQ(fm.measure.type, MeasureType::MDI);
    EXPECT_EQ(std::get<int64_t>(fm.measure.value), 10);
}