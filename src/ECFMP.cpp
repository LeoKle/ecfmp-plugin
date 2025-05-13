#include "ECFMP.h"

#include "Version.h"

namespace ecfmp {
ECFMP::ECFMP()
    : EuroScopePlugIn::CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE, PLUGIN_NAME, PLUGIN_VERSION, PLUGIN_AUTHOR,
                               PLUGIN_LICENSE) {
    this->m_pilotManager = std::make_shared<ecfmp::managers::PilotManager>();
}
ECFMP::~ECFMP() {}

void ECFMP::OnRadarTargetPositionUpdate(EuroScopePlugIn::CRadarTarget radartarget) {
    this->m_pilotManager->updatePilot(ecfmp::types::Pilot::fromCFlightPlan(radartarget.GetCorrelatedFlightPlan()));
}

void ECFMP::OnFlightPlanDisconnect(EuroScopePlugIn::CFlightPlan flightplan) {
    this->m_pilotManager->onPilotDisconnect(flightplan.GetCallsign());
}

void ECFMP::OnFlightPlanFlightPlanDataUpdate(EuroScopePlugIn::CFlightPlan flightplan) {
    this->m_pilotManager->updatePilot(ecfmp::types::Pilot::fromCFlightPlan(flightplan));
}

void ECFMP::OnFlightPlanControllerAssignedDataUpdate(EuroScopePlugIn::CFlightPlan flightplan, int datatype) {}
void ECFMP::OnAirportRunwayActivityChanged() {}

}  // namespace ecfmp