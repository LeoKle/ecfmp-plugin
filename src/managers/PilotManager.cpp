#include "PilotManager.h"

using namespace ecfmp::managers;

PilotManager::PilotManager() {}

PilotManager::~PilotManager() {}

void PilotManager::updatePilot(const ecfmp::types::Pilot& pilot) {
    std::lock_guard<std::mutex> lock(m_pilotsLock);
    m_pilots[pilot.getCallsign()] = pilot;
}

void PilotManager::onPilotDisconnect(const std::string& callsign) {
    std::lock_guard<std::mutex> lock(m_pilotsLock);
    auto it = m_pilots.find(callsign);
    if (it != m_pilots.end()) {
        it->second.setDisconnected(true);
    }
}

void PilotManager::removePilot(const std::string& callsign) {
    std::lock_guard<std::mutex> lock(m_pilotsLock);
    m_pilots.erase(callsign);
}

const bool PilotManager::pilotExists(const std::string& callsign) const {
    std::lock_guard<std::mutex> lock(m_pilotsLock);
    return m_pilots.find(callsign) != m_pilots.end();
}

ecfmp::types::Pilot PilotManager::getPilot(const std::string& callsign) const {
    std::lock_guard<std::mutex> lock(m_pilotsLock);
    auto it = m_pilots.find(callsign);
    if (it != m_pilots.end()) {
        return it->second;
    }
    throw std::runtime_error("Pilot not found");
}