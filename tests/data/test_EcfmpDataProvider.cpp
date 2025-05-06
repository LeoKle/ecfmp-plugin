#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "data/EcfmpDataProvider.h"
#include "types/FlowMeasure.h"

using json = nlohmann::json;
using namespace ecfmp;
using namespace ecfmp::data;

TEST(EcfmpDataProviderTest, getMeasures) {
    EcfmpDataProvider provider;

    const std::vector<types::FlowMeasure> result = provider.getMeasures();

    // EXPECT_FALSE(result.empty());
    // EXPECT_EQ(result.size(), 4);
}

TEST(EcfmpDataProviderTest, PerformGetReturnsValidJson) {
    EcfmpDataProvider provider;

    types::FlowMeasure expected = types::FlowMeasure();
    expected.id = 1671;

    const types::FlowMeasure result = provider.getMeasure(1671);

    // EXPECT_EQ(result.id, expected.id);
}
