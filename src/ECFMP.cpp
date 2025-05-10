#include "ECFMP.h"

#include "Version.h"

namespace ecfmp {
ECFMP::ECFMP()
    : EuroScopePlugIn::CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE, PLUGIN_NAME, PLUGIN_VERSION, PLUGIN_AUTHOR,
                               PLUGIN_LICENSE) {}
ECFMP::~ECFMP() {}

void ECFMP::OnRadarTargetPositionUpdate(EuroScopePlugIn::CRadarTarget radartarget) {}
void ECFMP::OnFlightPlanDisconnect(EuroScopePlugIn::CFlightPlan flightplan) {}
void ECFMP::OnFlightPlanFlightPlanDataUpdate(EuroScopePlugIn::CFlightPlan flightplan) {}
void ECFMP::OnFlightPlanControllerAssignedDataUpdate(EuroScopePlugIn::CFlightPlan flightplan, int datatype) {}
void ECFMP::OnAirportRunwayActivityChanged() {}

}  // namespace ecfmp