#include <gtest/gtest.h>

TEST(SampleTest, AssertionTrue) { EXPECT_TRUE(true); }

TEST(SampleTest, AssertionEqual) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}