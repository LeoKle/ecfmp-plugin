#pragma once

#include <atomic>
#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <set>
#include <string>
#include <thread>
#include <vector>

#include "IFlowMeasureDataProvider.h"
#include "api/IRestApi.h"
#include "types/FlowMeasure.h"

using json = nlohmann::json;

namespace ecfmp::data {
class EcfmpDataProvider : public IFlowMeasureDataProvider {
   public:
    EcfmpDataProvider(std::unique_ptr<ecfmp::api::IRestApi> restApi);
    ~EcfmpDataProvider() override;

    std::map<int64_t, types::FlowMeasure> getMeasures() override;
    types::FlowMeasure getMeasure(const int64_t measureId) override;

    void update() override;

   private:
    std::unique_ptr<ecfmp::api::IRestApi> m_restApi;

    std::mutex m_measuresLock;
    std::map<int64_t, types::FlowMeasure> m_measures;

    void thread();
    void pullMeasures();

    std::thread m_workerThread;
    std::mutex m_workerMutex;
    std::condition_variable m_workerCv;
    std::atomic<bool> m_exitThread{false};
    std::atomic<bool> m_workRequested{false};
};
}  // namespace ecfmp::data