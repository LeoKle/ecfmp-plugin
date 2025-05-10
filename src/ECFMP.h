#pragma once

#include <memory>
#include <string>

#pragma warning(push, 0)
#include "EuroScopePlugIn.h"
#pragma warning(pop)

namespace ecfmp {
class ECFMP : public EuroScopePlugIn::CPlugIn {
   public:
    ECFMP();
    ~ECFMP();

    void DisplayMessage(const std::string &message, const std::string &sender = "ECFMP");

    void OnRadarTargetPositionUpdate(EuroScopePlugIn::CRadarTarget radartarget) override;
    void OnFlightPlanDisconnect(EuroScopePlugIn::CFlightPlan flightplan) override;
    void OnFlightPlanFlightPlanDataUpdate(EuroScopePlugIn::CFlightPlan flightplan) override;
    void OnFlightPlanControllerAssignedDataUpdate(EuroScopePlugIn::CFlightPlan flightplan, int datatype) override;
    void OnAirportRunwayActivityChanged() override;
};
}  // namespace ecfmp
