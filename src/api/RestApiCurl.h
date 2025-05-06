#include <curl/curl.h>

#include <mutex>
#include <nlohmann/json.hpp>
#include <string>

#include "IRestApi.h"

namespace ecfmp::api {
class RestApiCurl : public IRestApi {
   public:
    RestApiCurl(const std::string& baseUrl);
    ~RestApiCurl() override;

    const nlohmann::json performGET(const std::string& endpoint) override;
    const nlohmann::json performPOST(const std::string& endpoint, const nlohmann::json data) override;
    const nlohmann::json performPATCH(const std::string& endpoint, const nlohmann::json data) override;
    const nlohmann::json performDELETE(const std::string& endpoint) override;

   private:
    struct CurlHandle {
        std::mutex lock;
        CURL* socket;

        CurlHandle() : lock(), socket(curl_easy_init()) {}
    };

    std::string m_baseUrl;
    CurlHandle m_getHandle;
    CurlHandle m_postHandle;
    CurlHandle m_patchHandle;
    CurlHandle m_deleteHandle;
};
}  // namespace ecfmp::api