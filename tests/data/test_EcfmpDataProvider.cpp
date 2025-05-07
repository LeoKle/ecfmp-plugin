#include <gtest/gtest.h>

#include <memory>
#include <nlohmann/json.hpp>

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
    tests::api::RestApiMock* m_apiRaw;
    std::unique_ptr<EcfmpDataProvider> m_ecfmpDataProvider;

    void SetUp() override {
        auto mock = std::make_unique<tests::api::RestApiMock>();
        m_apiRaw = mock.get();
        m_ecfmpDataProvider = std::make_unique<EcfmpDataProvider>(std::move(mock));
    }
};

TEST_F(EcfmpDataProviderTest, getMeasures) {
    m_apiRaw->setReturnJson(tests::api::example_data::flowMeasureArray);

    const std::vector<types::FlowMeasure> result = m_ecfmpDataProvider->getMeasures();

    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result[0].id, 1672);
    EXPECT_EQ(result[1].id, 1673);
    EXPECT_EQ(result[2].id, 1675);
    EXPECT_EQ(result[3].id, 1676);
    EXPECT_EQ(result[4].id, 1677);
}

TEST_F(EcfmpDataProviderTest, getMeasure) {
    const int64_t expectedMeasureId = 1675;
    m_apiRaw->setReturnJson(tests::api::example_data::singleFlowMeasure);
    const types::FlowMeasure result = m_ecfmpDataProvider->getMeasure(expectedMeasureId);

    EXPECT_EQ(result.id, expectedMeasureId);
}
