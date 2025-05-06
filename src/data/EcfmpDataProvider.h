#pragma once

#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string>

#include "IFlowMeasureDataProvider.h"
#include "api/IRestApi.h"
#include "types/FlowMeasure.h"

using json = nlohmann::json;

namespace ecfmp::data {
class EcfmpDataProvider : public IFlowMeasureDataProvider {
   public:
    EcfmpDataProvider(std::unique_ptr<ecfmp::api::IRestApi> restApi);
    ~EcfmpDataProvider() = default;

    std::vector<types::FlowMeasure> getMeasures() override;

    types::FlowMeasure getMeasure(const int64_t measureId) override;

   private:
    std::unique_ptr<ecfmp::api::IRestApi> m_restApi;
};
}  // namespace ecfmp::data