#pragma once

#include <map>
#include <mutex>
#include <string>

#include "interfaces/IPilotManager.h"
#include "types/Pilot.h"

namespace ecfmp::managers {
class PilotManager : public ecfmp::interfaces::IPilotManager {
   public:
    PilotManager();
    ~PilotManager() override;

    void updatePilot(const ecfmp::types::Pilot& pilot) override;
    void onPilotDisconnect(const std::string& callsign) override;
    void removePilot(const std::string& callsign) override;
    const bool pilotExists(const std::string& callsign) const override;
    const ecfmp::types::Pilot getPilot(const std::string& callsign) const override;

   private:
    mutable std::mutex m_pilotsLock;
    std::map<std::string, ecfmp::types::Pilot> m_pilots;
};
}  // namespace ecfmp::managers