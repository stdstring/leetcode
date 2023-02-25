#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minCostSetTime(int startAt, int moveCost, int pushCost, int targetSeconds) const
    {
        constexpr int maxValue = 99;
        int minCost = INT_MAX;
        if (targetSeconds <= maxValue)
            minCost = std::min(minCost, getCost(targetSeconds, false, startAt, moveCost, pushCost));
        const int usualMinutes = targetSeconds / 60;
        const int usualSeconds = targetSeconds % 60;
        if ((usualMinutes > 0) && (usualMinutes <= maxValue))
        {
            const int usualMinutesDigit0 = usualMinutes % 10;
            minCost = std::min(minCost, getCost(usualMinutes, false, startAt, moveCost, pushCost) + getCost(usualSeconds, true, usualMinutesDigit0, moveCost, pushCost));
        }
        if ((usualMinutes > 1) && (usualSeconds + 60 <= maxValue))
        {
            const int altMinutes = usualMinutes - 1;
            const int altSeconds = usualSeconds + 60;
            const int altMinutesDigit0 = altMinutes % 10;
            minCost = std::min(minCost, getCost(altMinutes, false, startAt, moveCost, pushCost) + getCost(altSeconds, true, altMinutesDigit0, moveCost, pushCost));
        }
        return minCost;
    }

private:
    [[nodiscard]] int getMoveCost(int digitFrom, int digitTo, int moveCost) const
    {
        return (digitFrom == digitTo ? 0 : 1) * moveCost;
    }

    [[nodiscard]] int getCost(int value, bool isLeadZeroSignificant, int startAt, int moveCost, int pushCost) const
    {
        const int digit1 = value / 10;
        const int digit0 = value % 10;
        return value < 10 && !isLeadZeroSignificant ?
               getMoveCost(startAt, digit0, moveCost) + pushCost :
               getMoveCost(startAt, digit1, moveCost) + getMoveCost(digit1, digit0, moveCost) + 2 * pushCost;
    }
};

}

namespace MinCostToSetCookingTimeTask
{

TEST(MinCostToSetCookingTimeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.minCostSetTime(1, 2, 1, 600));
    ASSERT_EQ(6, solution.minCostSetTime(0, 1, 2, 76));
}

TEST(MinCostToSetCookingTimeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(896, solution.minCostSetTime(9, 50, 199, 5990));
}

}