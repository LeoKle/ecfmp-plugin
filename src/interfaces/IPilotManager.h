#pragma once

#include <string>

#include "types/Pilot.h"

namespace ecfmp::interfaces {
class IPilotManager {
   public:
    virtual ~IPilotManager() = default;

    virtual void updatePilot(const types::Pilot& pilot) = 0;
    virtual void onPilotDisconnect(const std::string& callsign) = 0;
    virtual void removePilot(const std::string& callsign) = 0;
    virtual const bool pilotExists(const std::string& callsign) const = 0;
    virtual const types::Pilot getPilot(const std::string& callsign) const = 0;
};
}  // namespace ecfmp::interfaces