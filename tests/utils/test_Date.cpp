#include <gtest/gtest.h>

#include <chrono>

#include "utils/Date.h"

// Helper to construct utc_clock::time_point from Y/M/D H:M:S.ms
std::chrono::utc_clock::time_point makeTimePoint(int year, unsigned month, unsigned day, int hour = 0, int minute = 0,
                                                 int second = 0, int millisecond = 0) {
    using namespace std::chrono;

    auto date = std::chrono::year_month_day{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};
    sys_time<milliseconds> sysTime =
        sys_days{date} + hours{hour} + minutes{minute} + seconds{second} + milliseconds{millisecond};

    return utc_clock::from_sys(sysTime);
}

TEST(TimestampToIsoStringTest, ZeroTimestamp) {
    auto tp = std::chrono::utc_clock::time_point{};
    EXPECT_EQ(utils::Date::timestampToIsoString(tp), "1970-01-01T00:00:00.000Z");
}

TEST(TimestampToIsoStringTest, EpochTime) {
    auto tp = makeTimePoint(1970, 1, 1, 0, 0, 0, 0);
    EXPECT_EQ(utils::Date::timestampToIsoString(tp), "1970-01-01T00:00:00.000Z");
}

TEST(TimestampToIsoStringTest, ModernTimeWithMilliseconds) {
    auto tp = makeTimePoint(2023, 3, 10, 15, 45, 30, 123);
    EXPECT_EQ(utils::Date::timestampToIsoString(tp), "2023-03-10T15:45:30.123Z");
}

TEST(TimestampToIsoStringTest, HistoricalTime) {
    auto tp = makeTimePoint(1965, 12, 31, 23, 59, 59, 999);
    EXPECT_EQ(utils::Date::timestampToIsoString(tp), "1969-12-31T23:59:59.999Z");
}

TEST(TimestampToIsoStringTest, LowMillisecondsPadding) {
    auto tp = makeTimePoint(1980, 6, 5, 12, 30, 0, 9);
    EXPECT_EQ(utils::Date::timestampToIsoString(tp), "1980-06-05T12:30:00.009Z");
}

TEST(isoStringToTimestampTest, ValidIsoTimestamp) {
    auto tp = makeTimePoint(1965, 12, 31, 23, 59, 59, 999);
    std::string isoString = "1965-12-31T23:59:59.999Z";

    EXPECT_EQ(utils::Date::isoStringToTimestamp(isoString), tp);
}

TEST(isoStringToTimestampTest, ValidIsoTimestamp2) {
    auto tp = makeTimePoint(2023, 3, 10, 15, 45, 30, 123);
    std::string isoString = "2023-03-10T15:45:30.123Z";

    EXPECT_EQ(utils::Date::isoStringToTimestamp(isoString), tp);
}

TEST(isoStringToTimestampTest, ValidIsoTimestamp3) {
    auto tp = makeTimePoint(2060, 12, 30, 0, 0, 0, 0);
    std::string isoString = "2060-12-30T00:00:00.000Z";

    EXPECT_EQ(utils::Date::isoStringToTimestamp(isoString), tp);
}