#include "EcfmpDataProvider.h"

using namespace ecfmp;
using namespace ecfmp::data;

static std::size_t receiveCurlGet(void* ptr, std::size_t size, std::size_t nmemb, void* stream) {
    std::size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(stream);
    response->append(static_cast<char*>(ptr), totalSize);
    return totalSize;
}

EcfmpDataProvider::EcfmpDataProvider() : m_baseUrl("https://ecfmp.vatsim.net") {
    curl_easy_setopt(m_getHandle.socket, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(m_getHandle.socket, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(m_getHandle.socket, CURLOPT_HTTP_VERSION, static_cast<long>(CURL_HTTP_VERSION_1_1));
    curl_easy_setopt(m_getHandle.socket, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(m_getHandle.socket, CURLOPT_WRITEFUNCTION, receiveCurlGet);
    curl_easy_setopt(m_getHandle.socket, CURLOPT_TIMEOUT, 2L);
}

types::FlowMeasure EcfmpDataProvider::getMeasure(const int64_t measureId) {
    const auto json = this->performGet("/api/v1/flow-measure/" + std::to_string(measureId));

    if (json.is_object()) {
        return types::FlowMeasure::fromJson(json);
    }

    return types::FlowMeasure();
}

std::vector<types::FlowMeasure> EcfmpDataProvider::getMeasures() {
    const auto json = this->performGet("/api/v1/flow-measure");

    std::vector<types::FlowMeasure> measures;
    if (json.is_array()) {
        for (const auto& measure : json) {
            measures.push_back(types::FlowMeasure::fromJson(measure));
        }
    }

    return measures;
}

const json EcfmpDataProvider::performGet(const std::string& endpoint) {
    std::string response;
    const std::string url = m_baseUrl + endpoint;

    std::lock_guard<std::mutex> lock(m_getHandle.lock);
    curl_easy_setopt(m_getHandle.socket, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_getHandle.socket, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(m_getHandle.socket);

    if (res != CURLE_OK) {
        return json();
    }

    try {
        return json::parse(response);
    } catch (const json::parse_error& e) {
        return json();
    }
}
