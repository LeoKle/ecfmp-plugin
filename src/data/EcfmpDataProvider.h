#pragma once

#include "IFlowMeasureDataProvider.h"
#include "types/FlowMeasure.h"

namespace ecfmp::data {
class EcfmpDataProvider : public IFlowMeasureDataProvider {
   public:
    EcfmpDataProvider();
    ~EcfmpDataProvider() = default;

    std::vector<types::FlowMeasure> getMeasures() override;

    types::FlowMeasure getMeasure(const int64_t measureId) override;
};
}  // namespace ecfmp::data