#pragma once

#include <chrono>
#include <string>

#pragma warning(push, 0)
#include "EuroScopePlugIn.h"
#pragma warning(pop)

namespace ecfmp::types {
class Pilot {
    Pilot();

   private:
    struct PositionData {
        float latitude;
        float longitude;
    };

    struct FlightplanData {
        std::string adep;
        std::string ades;
        std::string alternate;
        std::string route;
    };

    std::string callsign;
    std::chrono::utc_clock::time_point lastUpdate;
    bool disconnected = false;

    PositionData position;
    FlightplanData flightplan;

   public:
    void update(const EuroScopePlugIn::CFlightPlan& flightplan);
    static Pilot fromCFlightPlan(const EuroScopePlugIn::CFlightPlan& flightplan);
};
}  // namespace ecfmp::types