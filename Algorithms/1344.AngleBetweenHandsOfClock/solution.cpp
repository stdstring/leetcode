#include <cstdlib>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double angleClock(int hour, int minutes) const
    {
        hour = hour == 12 ? 0 : hour;
        const double minutesAngle = 360.0 * minutes / 60.0;
        constexpr double hourSectorAngle = 360.0 / 12;
        const double hourAngle = hour * hourSectorAngle + hourSectorAngle * minutes / 60.0;
        const double delta = std::abs(hourAngle - minutesAngle);
        return delta > 180 ? 360 - delta : delta;
    }
};

}

namespace AngleBetweenHandsOfClockTask
{

TEST(AngleBetweenHandsOfClockTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_DOUBLE_EQ(165, solution.angleClock(12, 30));
    ASSERT_DOUBLE_EQ(75, solution.angleClock(3, 30));
    ASSERT_DOUBLE_EQ(7.5, solution.angleClock(3, 15));
}

TEST(AngleBetweenHandsOfClockTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_DOUBLE_EQ(76.5, solution.angleClock(1, 57));
}

}