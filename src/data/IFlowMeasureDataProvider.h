#pragma once

#include <cstdint>
#include <map>

#include "types/FlowMeasure.h"

namespace ecfmp::data {
class IFlowMeasureDataProvider {
   public:
    virtual ~IFlowMeasureDataProvider() = default;

    virtual std::map<int64_t, types::FlowMeasure> getMeasures() = 0;
    virtual types::FlowMeasure getMeasure(const int64_t measureId) = 0;
    virtual void update() = 0;
};
}  // namespace ecfmp::data