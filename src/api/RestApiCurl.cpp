#include "RestApiCurl.h"

using namespace ecfmp::api;
using json = nlohmann::json;

static std::size_t receiveCurlGet(void* ptr, std::size_t size, std::size_t nmemb, void* stream) {
    std::size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(stream);
    response->append(static_cast<char*>(ptr), totalSize);
    return totalSize;
}

static std::size_t receiveCurlPost(void* ptr, std::size_t size, std::size_t nmemb, void* stream) {
    std::size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(stream);
    response->append(static_cast<char*>(ptr), totalSize);
    return totalSize;
}

static std::size_t receiveCurlPatch(void* ptr, std::size_t size, std::size_t nmemb, void* stream) {
    std::size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(stream);
    response->append(static_cast<char*>(ptr), totalSize);
    return totalSize;
}

static std::size_t receiveCurlDelete(void* ptr, std::size_t size, std::size_t nmemb, void* stream) {
    std::size_t totalSize = size * nmemb;
    std::string* response = static_cast<std::string*>(stream);
    response->append(static_cast<char*>(ptr), totalSize);
    return totalSize;
}

RestApiCurl::RestApiCurl(const std::string& baseUrl) : m_baseUrl(baseUrl) {
    /* configure the get request */
    curl_easy_setopt(m_getHandle.socket, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(m_getHandle.socket, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(m_getHandle.socket, CURLOPT_HTTP_VERSION, static_cast<long>(CURL_HTTP_VERSION_1_1));
    curl_easy_setopt(m_getHandle.socket, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(m_getHandle.socket, CURLOPT_WRITEFUNCTION, receiveCurlGet);
    curl_easy_setopt(m_getHandle.socket, CURLOPT_TIMEOUT, 2L);

    /* configure the post request */
    curl_easy_setopt(m_postHandle.socket, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(m_postHandle.socket, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(m_postHandle.socket, CURLOPT_HTTP_VERSION, static_cast<long>(CURL_HTTP_VERSION_1_1));
    curl_easy_setopt(m_postHandle.socket, CURLOPT_WRITEFUNCTION, receiveCurlPost);
    curl_easy_setopt(m_postHandle.socket, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(m_postHandle.socket, CURLOPT_VERBOSE, 1);
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Accept: application/json");
    // headers = curl_slist_append(headers, ("Authorization: Bearer " + AUTH_TOKEN_PLACEHOLDER).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(m_postHandle.socket, CURLOPT_HTTPHEADER, headers);

    /* configure the patch request */
    curl_easy_setopt(m_patchHandle.socket, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(m_patchHandle.socket, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(m_patchHandle.socket, CURLOPT_HTTP_VERSION, static_cast<long>(CURL_HTTP_VERSION_1_1));
    curl_easy_setopt(m_patchHandle.socket, CURLOPT_WRITEFUNCTION, receiveCurlPatch);
    curl_easy_setopt(m_patchHandle.socket, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(m_patchHandle.socket, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(m_patchHandle.socket, CURLOPT_HTTPHEADER, headers);

    /* configure the delete request */
    curl_easy_setopt(m_deleteHandle.socket, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(m_deleteHandle.socket, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(m_deleteHandle.socket, CURLOPT_HTTP_VERSION, static_cast<long>(CURL_HTTP_VERSION_1_1));
    curl_easy_setopt(m_deleteHandle.socket, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(m_deleteHandle.socket, CURLOPT_WRITEFUNCTION, receiveCurlDelete);
    curl_easy_setopt(m_deleteHandle.socket, CURLOPT_TIMEOUT, 2L);
}

RestApiCurl::~RestApiCurl() {
    if (nullptr != m_getHandle.socket) {
        std::lock_guard guard(m_getHandle.lock);
        curl_easy_cleanup(m_getHandle.socket);
        m_getHandle.socket = nullptr;
    }

    if (nullptr != m_postHandle.socket) {
        std::lock_guard guard(m_postHandle.lock);
        curl_easy_cleanup(m_postHandle.socket);
        m_postHandle.socket = nullptr;
    }

    if (nullptr != m_patchHandle.socket) {
        std::lock_guard guard(m_patchHandle.lock);
        curl_easy_cleanup(m_patchHandle.socket);
        m_patchHandle.socket = nullptr;
    }

    if (nullptr != m_deleteHandle.socket) {
        std::lock_guard guard(m_deleteHandle.lock);
        curl_easy_cleanup(m_deleteHandle.socket);
        m_deleteHandle.socket = nullptr;
    }
}

const json RestApiCurl::performGET(const std::string& endpoint) {
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

const json RestApiCurl::performPOST(const std::string& endpoint, const nlohmann::json data) {
    std::string response;
    const std::string url = m_baseUrl + endpoint;

    std::lock_guard<std::mutex> lock(m_postHandle.lock);
    curl_easy_setopt(m_postHandle.socket, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_postHandle.socket, CURLOPT_POSTFIELDS, data.dump().c_str());
    curl_easy_setopt(m_postHandle.socket, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(m_postHandle.socket);

    if (res != CURLE_OK) {
        return json();
    }

    try {
        return json::parse(response);
    } catch (const json::parse_error& e) {
        return json();
    }
}

const json RestApiCurl::performPATCH(const std::string& endpoint, const nlohmann::json data) { return json(); }
const json RestApiCurl::performDELETE(const std::string& endpoint) { return json(); }