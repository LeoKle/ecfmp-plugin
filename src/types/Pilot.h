#pragma once

#include <chrono>
#include <string>

#pragma warning(push, 0)
#include "EuroScopePlugIn.h"
#pragma warning(pop)

namespace ecfmp::types {
class Pilot {
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

    Pilot();
    Pilot(const std::string& callsign, const std::chrono::utc_clock::time_point& lastUpdate, bool disconnected,
          const PositionData& position, const FlightplanData& flightplan);

   private:
    std::string callsign;
    std::chrono::utc_clock::time_point lastUpdate;
    bool disconnected = false;

    PositionData position;
    FlightplanData flightplan;

   public:
    void update(const EuroScopePlugIn::CFlightPlan& flightplan);
    static Pilot fromCFlightPlan(const EuroScopePlugIn::CFlightPlan& flightplan);

    const std::string& getCallsign() const { return callsign; }
    const std::chrono::utc_clock::time_point& getLastUpdate() const { return lastUpdate; }
    bool isDisconnected() const { return disconnected; }
    const PositionData& getPosition() const { return position; }
    const FlightplanData& getFlightplan() const { return flightplan; }
};
}  // namespace ecfmp::types