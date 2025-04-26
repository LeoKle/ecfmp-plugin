#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "types/Measure.h"

using json = nlohmann::json;

TEST(MeasureTest, TestMeasureTypeFromString) {
    using namespace ecfmp::types;

    EXPECT_EQ(Measure::measureTypeFromString("minimum_departure_interval"), MeasureType::MDI);
    EXPECT_EQ(Measure::measureTypeFromString("average_departure_interval"), MeasureType::ADI);
    EXPECT_EQ(Measure::measureTypeFromString("per_hour"), MeasureType::PER_HOUR);
    EXPECT_EQ(Measure::measureTypeFromString("miles_in_trail"), MeasureType::MIT);
    EXPECT_EQ(Measure::measureTypeFromString("max_ias"), MeasureType::MAX_IAS);
    EXPECT_EQ(Measure::measureTypeFromString("max_mach"), MeasureType::MAX_MACH);
    EXPECT_EQ(Measure::measureTypeFromString("ias_reduction"), MeasureType::IAS_REDUCTION);
    EXPECT_EQ(Measure::measureTypeFromString("mach_reduction"), MeasureType::MACH_REDUCTION);
    EXPECT_EQ(Measure::measureTypeFromString("prohibit"), MeasureType::PROHIBIT);
    EXPECT_EQ(Measure::measureTypeFromString("ground_stop"), MeasureType::GROUND_STOP);
    EXPECT_EQ(Measure::measureTypeFromString("mandatory_route"), MeasureType::MANDATORY_ROUTE);
}

TEST(MeasureTest, TestMeasureFromJson) {
    using namespace ecfmp::types;

    const json mdiJson = {{"type", "minimum_departure_interval"}, {"value", 10}};
    const auto measureMdi = Measure::fromJson(mdiJson);
    EXPECT_EQ(measureMdi.type, MeasureType::MDI);
    EXPECT_EQ(std::get<int64_t>(measureMdi.value), 10);

    const json adiJson = {{"type", "average_departure_interval"}, {"value", 20}};
    const auto measureAdi = Measure::fromJson(adiJson);
    EXPECT_EQ(measureAdi.type, MeasureType::ADI);
    EXPECT_EQ(std::get<int64_t>(measureAdi.value), 20);

    const json perHourJson = {{"type", "per_hour"}, {"value", 30}};
    const auto measurePerHour = Measure::fromJson(perHourJson);
    EXPECT_EQ(measurePerHour.type, MeasureType::PER_HOUR);
    EXPECT_EQ(std::get<int64_t>(measurePerHour.value), 30);

    const json mitJson = {{"type", "miles_in_trail"}, {"value", 40}};
    const auto measureMit = Measure::fromJson(mitJson);
    EXPECT_EQ(measureMit.type, MeasureType::MIT);
    EXPECT_EQ(std::get<int64_t>(measureMit.value), 40);

    const json maxIasJson = {{"type", "max_ias"}, {"value", 250}};
    const auto measureMaxIas = Measure::fromJson(maxIasJson);
    EXPECT_EQ(measureMaxIas.type, MeasureType::MAX_IAS);
    EXPECT_EQ(std::get<int64_t>(measureMaxIas.value), 250);

    const json maxMachJson = {{"type", "max_mach"}, {"value", 780}};
    const auto measureMaxMach = Measure::fromJson(maxMachJson);
    EXPECT_EQ(measureMaxMach.type, MeasureType::MAX_MACH);
    EXPECT_EQ(std::get<int64_t>(measureMaxMach.value), 780);

    const json iasReductionJson = {{"type", "ias_reduction"}, {"value", 20}};
    const auto measureIasReduction = Measure::fromJson(iasReductionJson);
    EXPECT_EQ(measureIasReduction.type, MeasureType::IAS_REDUCTION);
    EXPECT_EQ(std::get<int64_t>(measureIasReduction.value), 20);

    const json machReductionJson = {{"type", "mach_reduction"}, {"value", 2}};
    const auto measureMachReduction = Measure::fromJson(machReductionJson);
    EXPECT_EQ(measureMachReduction.type, MeasureType::MACH_REDUCTION);
    EXPECT_EQ(std::get<int64_t>(measureMachReduction.value), 2);

    const json prohibitJson = {{"type", "prohibit"}, {"value", nullptr}};
    const auto measureProhibit = Measure::fromJson(prohibitJson);
    EXPECT_EQ(measureProhibit.type, MeasureType::PROHIBIT);
    EXPECT_EQ(std::get<int64_t>(measureProhibit.value), 0);

    const json mandatoryRouteJson = {{"type", "mandatory_route"}, json::array({"value", {"route1", "route2"}})};
    const auto measureMandatoryRoute = Measure::fromJson(mandatoryRouteJson);
    EXPECT_EQ(measureMandatoryRoute.type, MeasureType::MANDATORY_ROUTE);
    EXPECT_EQ(std::get<std::vector<std::string>>(measureMandatoryRoute.value),
              std::vector<std::string>({"route1", "route2"}));
}