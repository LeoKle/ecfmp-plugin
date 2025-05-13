#pragma once

#include <chrono>
#include <string>

#pragma warning(push, 0)
#include "EuroScopePlugIn.h"
#pragma warning(pop)

namespace ecfmp::types {
class Pilot {
   public:
    struct PositionData {
        float latitude;
        float longitude;
        PositionData(float latitude = 0.0f, float longitude = 0.0f) : latitude(latitude), longitude(longitude) {}
    };

    struct FlightplanData {
        std::string adep;
        std::string ades;
        std::string alternate;
        std::string route;
        FlightplanData(const std::string& adep = "", const std::string& ades = "", const std::string& alternate = "",
                       const std::string& route = "")
            : adep(adep), ades(ades), alternate(alternate), route(route) {}
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
    // TODO: kill / remove any ES references
    void update(const EuroScopePlugIn::CFlightPlan& flightplan);
    static Pilot fromCFlightPlan(const EuroScopePlugIn::CFlightPlan& flightplan);

    const std::string& getCallsign() const { return callsign; }
    const std::chrono::utc_clock::time_point& getLastUpdate() const { return lastUpdate; }
    bool isDisconnected() const { return disconnected; }
    const PositionData& getPosition() const { return position; }
    const FlightplanData& getFlightplan() const { return flightplan; }

    void setDisconnected(bool disconnected) { this->disconnected = disconnected; }
};
}  // namespace ecfmp::types