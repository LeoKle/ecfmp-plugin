#pragma once

#include <cstdint>
#include <list>

#include "types/FlowMeasure.h"

namespace ecfmp::data {
class IFlowMeasureDataProvider {
   public:
    virtual ~IFlowMeasureDataProvider() = default;

    virtual std::vector<types::FlowMeasure> getMeasures() = 0;
    virtual types::FlowMeasure getMeasure(const int64_t measureId) = 0;
};
}  // namespace ecfmp::data