#include <gtest/gtest.h>

#include <chrono>
#include <memory>
#include <nlohmann/json.hpp>
#include <thread>

#include "api/IRestApi.h"
#include "data/EcfmpDataProvider.h"
#include "tests/api/EcfmpExampleJsons.h"
#include "tests/api/RestApiMock.h"
#include "types/FlowMeasure.h"

using json = nlohmann::json;
using namespace ecfmp;
using namespace ecfmp::data;

class EcfmpDataProviderTest : public ::testing::Test {
   protected:
    std::unique_ptr<EcfmpDataProvider> m_ecfmpDataProvider;

    void SetUp() override {
        auto mock = std::make_unique<tests::api::RestApiMock>();
        mock->setReturnJson(tests::api::example_data::flowMeasureArray);
        m_ecfmpDataProvider = std::make_unique<EcfmpDataProvider>(std::move(mock));

        // pull data and sleep to allow the data to be processed
        m_ecfmpDataProvider->update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
};

TEST_F(EcfmpDataProviderTest, getMeasures) {
    const std::map<int64_t, types::FlowMeasure> result = m_ecfmpDataProvider->getMeasures();

    EXPECT_EQ(result.size(), 5);
}

TEST_F(EcfmpDataProviderTest, getMeasure) {
    const int64_t expectedMeasureId = 1672;
    const types::FlowMeasure result = m_ecfmpDataProvider->getMeasure(expectedMeasureId);

    EXPECT_EQ(result.id, expectedMeasureId);
}
