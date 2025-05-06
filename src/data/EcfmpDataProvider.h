#pragma once

#include <curl/curl.h>

#include <mutex>
#include <nlohmann/json.hpp>
#include <string>

#include "IFlowMeasureDataProvider.h"
#include "types/FlowMeasure.h"

using json = nlohmann::json;

namespace ecfmp::data {
class EcfmpDataProvider : public IFlowMeasureDataProvider {
   public:
    EcfmpDataProvider();
    ~EcfmpDataProvider() = default;

    std::vector<types::FlowMeasure> getMeasures() override;

    types::FlowMeasure getMeasure(const int64_t measureId) override;

   private:
    struct CurlHandle {
        std::mutex lock;
        CURL* socket;

        CurlHandle() : lock(), socket(curl_easy_init()) {}
    };

    CurlHandle m_getHandle;
    std::string m_baseUrl;

    const json performGet(const std::string& endpoint);
};
}  // namespace ecfmp::data