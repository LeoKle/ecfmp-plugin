#pragma once

#include <nlohmann/json.hpp>

#include "EcfmpExampleJsons.h"
#include "api/IRestApi.h"

namespace ecfmp::tests::api {
class RestApiMock : public ecfmp::api::IRestApi {
   public:
    RestApiMock() = default;
    ~RestApiMock() override = default;

    nlohmann::json m_returnJson = nlohmann::json();
    RestApiMock(const nlohmann::json returnJson) : m_returnJson(returnJson) {}
    void setReturnJson(const nlohmann::json returnJson) { this->m_returnJson = returnJson; }

    const nlohmann::json performGET(const std::string& endpoint) override { return this->m_returnJson; }
    const nlohmann::json performPOST(const std::string& endpoint, const nlohmann::json data) override {
        return this->m_returnJson;
    }
    const nlohmann::json performPATCH(const std::string& endpoint, const nlohmann::json data) override {
        return this->m_returnJson;
    }
    const nlohmann::json performDELETE(const std::string& endpoint) override { return this->m_returnJson; }
};
}  // namespace ecfmp::tests::api