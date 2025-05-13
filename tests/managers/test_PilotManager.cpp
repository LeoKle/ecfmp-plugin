#include <gtest/gtest.h>

#include <mutex>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "managers/PilotManager.h"
#include "types/Pilot.h"

using namespace ecfmp::managers;
using namespace ecfmp::types;

class PilotManagerTest : public ::testing::Test {
   protected:
    std::unique_ptr<PilotManager> manager;

    const Pilot pilotUpdate1 = Pilot("DLH123", std::chrono::utc_clock::now(), false, Pilot::PositionData(0.0f, 0.0f),
                                     Pilot::FlightplanData("EDDL", "EDDK", "EDDF", "ROUTE STRING"));

    void SetUp() override { manager = std::make_unique<PilotManager>(); }
};

TEST_F(PilotManagerTest, GetPilot_ExistingPilot) {
    manager->updatePilot(pilotUpdate1);

    auto retrievedPilot = manager->getPilot(pilotUpdate1.getCallsign());
    EXPECT_EQ(retrievedPilot.getCallsign(), pilotUpdate1.getCallsign());
    EXPECT_FALSE(retrievedPilot.isDisconnected());
}

TEST_F(PilotManagerTest, GetPilot_NonExistingPilot) {
    EXPECT_THROW(manager->getPilot("NONEXISTENT"), std::runtime_error);
}

TEST_F(PilotManagerTest, GetPilot_AfterPilotRemoved) {
    manager->updatePilot(pilotUpdate1);
    manager->removePilot(pilotUpdate1.getCallsign());

    EXPECT_THROW(manager->getPilot(pilotUpdate1.getCallsign()), std::runtime_error);
}

TEST_F(PilotManagerTest, GetPilot_AfterPilotDisconnected) {
    manager->updatePilot(pilotUpdate1);
    manager->onPilotDisconnect(pilotUpdate1.getCallsign());

    auto retrievedPilot = manager->getPilot(pilotUpdate1.getCallsign());
    EXPECT_EQ(retrievedPilot.getCallsign(), pilotUpdate1.getCallsign());
    EXPECT_TRUE(retrievedPilot.isDisconnected());
}