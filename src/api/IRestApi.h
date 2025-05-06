#include <nlohmann/json.hpp>
#include <string>

namespace ecfmp::api {
class IRestApi {
   public:
    virtual ~IRestApi() = default;

    virtual const nlohmann::json performGET(const std::string& endpoint) = 0;
    virtual const nlohmann::json performPOST(const std::string& endpoint, const nlohmann::json data) = 0;
    virtual const nlohmann::json performPATCH(const std::string& endpoint, const nlohmann::json data) = 0;
    virtual const nlohmann::json performDELETE(const std::string& endpoint) = 0;
};
}  // namespace ecfmp::api