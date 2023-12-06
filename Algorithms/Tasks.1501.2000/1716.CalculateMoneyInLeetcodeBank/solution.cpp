#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int totalMoney(int n) const
    {
        // 1 + 2 + 3 + 4 + 5 + 6 + 7 == 28
        constexpr int fullFirstWeekValue = 28;
        const int fullWeeks = n / 7;
        int result = fullWeeks * fullFirstWeekValue + (fullWeeks - 1) * 7 * fullWeeks / 2;
        for (int day = 1; day <= n % 7; ++day)
          result += (fullWeeks + day);
        return result;
    }
};

}

namespace CalculateMoneyInLeetcodeBankTask
{

TEST(CalculateMoneyInLeetcodeBankTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(10, solution.totalMoney(4));
    ASSERT_EQ(37, solution.totalMoney(10));
    ASSERT_EQ(96, solution.totalMoney(20));
}

}