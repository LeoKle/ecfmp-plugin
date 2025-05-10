#include "Pilot.h"

using namespace ecfmp::types;

Pilot::Pilot() : callsign(""), lastUpdate(std::chrono::utc_clock::now()), disconnected(false) {}

Pilot::Pilot(const std::string& callsign, const std::chrono::utc_clock::time_point& lastUpdate, bool disconnected,
             const PositionData& position, const FlightplanData& flightplan)
    : callsign(callsign),
      lastUpdate(lastUpdate),
      disconnected(disconnected),
      position(position),
      flightplan(flightplan) {}

void Pilot::update(const EuroScopePlugIn::CFlightPlan& flightplan) {
    this->lastUpdate = std::chrono::utc_clock::now();
    this->disconnected = false;

    // position data
    if (flightplan.GetCorrelatedRadarTarget().IsValid()) {
        // get the position of the flight using its radar target
        this->position.latitude =
            static_cast<float>(flightplan.GetCorrelatedRadarTarget().GetPosition().GetPosition().m_Latitude);
        this->position.longitude =
            static_cast<float>(flightplan.GetCorrelatedRadarTarget().GetPosition().GetPosition().m_Longitude);
    } else {
        // if we have no radar target we will use the fptrackposition
        // tends to be imprecise
        this->position.latitude = static_cast<float>(flightplan.GetFPTrackPosition().GetPosition().m_Latitude);
        this->position.longitude = static_cast<float>(flightplan.GetFPTrackPosition().GetPosition().m_Longitude);
    }

    this->flightplan.adep = flightplan.GetFlightPlanData().GetOrigin();
    this->flightplan.ades = flightplan.GetFlightPlanData().GetDestination();
    this->flightplan.alternate = flightplan.GetFlightPlanData().GetAlternate();
    this->flightplan.route = flightplan.GetFlightPlanData().GetRoute();
}

Pilot Pilot::fromCFlightPlan(const EuroScopePlugIn::CFlightPlan& flightplan) {
    Pilot pilot;
    pilot.callsign = flightplan.GetCallsign();
    pilot.update(flightplan);
    return pilot;
}