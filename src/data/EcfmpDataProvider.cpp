#include "EcfmpDataProvider.h"

using namespace ecfmp;
using namespace ecfmp::data;

EcfmpDataProvider::EcfmpDataProvider(std::unique_ptr<ecfmp::api::IRestApi> restApi) : m_restApi(std::move(restApi)) {}

types::FlowMeasure EcfmpDataProvider::getMeasure(const int64_t measureId) {
    const auto json = this->m_restApi->performGET("/api/v1/flow-measure/" + std::to_string(measureId));

    if (json.is_object()) {
        return types::FlowMeasure::fromJson(json);
    }

    return types::FlowMeasure();
}

std::vector<types::FlowMeasure> EcfmpDataProvider::getMeasures() {
    const auto json = this->m_restApi->performGET("/api/v1/flow-measure");

    std::vector<types::FlowMeasure> measures;
    if (json.is_array()) {
        for (const auto& measure : json) {
            measures.push_back(types::FlowMeasure::fromJson(measure));
        }
    }

    return measures;
}
