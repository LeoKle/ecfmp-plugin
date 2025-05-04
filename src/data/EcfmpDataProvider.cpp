#include "EcfmpDataProvider.h"

using namespace ecfmp;
using namespace ecfmp::data;

EcfmpDataProvider::EcfmpDataProvider() {}

types::FlowMeasure EcfmpDataProvider::getMeasures() { return types::FlowMeasure(); }

std::vector<types::FlowMeasure> EcfmpDataProvider::getMeasure(const int64_t measureId) {
    return std::vector<types::FlowMeasure>();
}