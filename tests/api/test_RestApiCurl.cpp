// #include <gtest/gtest.h>

// #include <memory>
// #include <nlohmann/json.hpp>
// #include <string>

// #include "api/RestApiCurl.h"

// using json = nlohmann::json;

// class RestApiCurlTest : public ::testing::Test {
//    protected:
//     std::unique_ptr<ecfmp::api::RestApiCurl> m_api;
//     std::string m_baseUrl;

//     void SetUp() override {
//         m_baseUrl = "test_url";
//         m_api = std::make_unique<ecfmp::api::RestApiCurl>(m_baseUrl);
//     }
// };

// TEST_F(RestApiCurlTest, TestPerformGET) {
//     const auto response = this->m_api->performGET("/posts");

//     ASSERT_FALSE(response.empty());
//     ASSERT_TRUE(response.is_array());
// }

// TEST_F(RestApiCurlTest, TestPerformGETNonArray) {
//     const auto response = this->m_api->performGET("/posts/1");

//     ASSERT_FALSE(response.empty());
//     ASSERT_FALSE(response.is_array());
// }

// TEST_F(RestApiCurlTest, TestPerformPOST) {
//     json testJson = R"(
//         {
//             "id": 1669,
//             "title": "Post 4"
//         }
//     )"_json;

//     const auto response = this->m_api->performPOST("/posts", testJson);
// }

// TEST_F(RestApiCurlTest, TestPerformPATCH) {
//     json testJson = R"(
//         {
//             "id": 1669,
//             "title": "Post 4"
//         }
//     )"_json;

//     const auto response = this->m_api->performPATCH("/posts", testJson);
// }

// TEST_F(RestApiCurlTest, TestPerformDELETE) { const auto response = this->m_api->performDELETE("/posts"); }