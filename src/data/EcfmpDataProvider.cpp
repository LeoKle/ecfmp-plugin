#include "EcfmpDataProvider.h"

using namespace ecfmp;
using namespace ecfmp::data;

constexpr auto updateCycle = std::chrono::minutes(5);

EcfmpDataProvider::EcfmpDataProvider(std::unique_ptr<ecfmp::api::IRestApi> restApi)
    : m_restApi(std::move(restApi)), m_measuresLock(), m_measures() {
    m_workerThread = std::thread(&EcfmpDataProvider::thread, this);
    this->update();
}

EcfmpDataProvider::~EcfmpDataProvider() {
    {
        std::lock_guard<std::mutex> lock(m_workerMutex);
        m_exitThread = true;
        m_workerCv.notify_one();
    }
    if (m_workerThread.joinable()) {
        m_workerThread.join();
    }
}

void EcfmpDataProvider::update() {
    {
        std::lock_guard<std::mutex> lock(m_workerMutex);
        m_workRequested = true;
    }
    m_workerCv.notify_one();
}

void EcfmpDataProvider::thread() {
    std::unique_lock<std::mutex> lock(m_workerMutex);

    while (true) {
        // Wait for either work to be requested or timeout
        bool timeout = !m_workerCv.wait_for(lock, updateCycle, [&]() { return m_workRequested || m_exitThread; });

        if (m_exitThread) break;

        if (m_workRequested || timeout) {
            m_workRequested = false;
            lock.unlock();
            pullMeasures();
            lock.lock();
        }
    }
}

void EcfmpDataProvider::pullMeasures() {
    const auto json = this->m_restApi->performGET("/api/v1/flow-measure");

    std::vector<types::FlowMeasure> newMeasures;
    std::set<int64_t> newIds;

    if (json.is_array()) {
        for (const auto& measureJson : json) {
            types::FlowMeasure measure = types::FlowMeasure::fromJson(measureJson);
            newMeasures.push_back(measure);
            newIds.insert(measure.id);
        }
    }

    std::lock_guard<std::mutex> lock(this->m_measuresLock);

    // Add or update measures
    for (const auto& measure : newMeasures) {
        this->m_measures[measure.id] = measure;
    }

    // Remove measures that no longer exist
    for (auto it = m_measures.begin(); it != m_measures.end();) {
        if (newIds.find(it->first) == newIds.end()) {
            it = m_measures.erase(it);
        } else {
            ++it;
        }
    }
}

types::FlowMeasure EcfmpDataProvider::getMeasure(const int64_t measureId) { return this->m_measures.at(measureId); }

std::map<int64_t, types::FlowMeasure> EcfmpDataProvider::getMeasures() { return this->m_measures; }
