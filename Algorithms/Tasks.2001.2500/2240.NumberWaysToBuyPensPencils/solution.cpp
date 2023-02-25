#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long waysToBuyPensPencils(int total, int cost1, int cost2) const
    {
        long long result = 0;
        for (int moneyOnPens = 0; moneyOnPens <= total; moneyOnPens += cost1)
        {
            const int restMoney = total - moneyOnPens;
            result += (1 + restMoney / cost2);
        }
        return result;
    }
};

}

namespace NumberWaysToBuyPensPencilsTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.waysToBuyPensPencils(20, 10, 5));
    ASSERT_EQ(1, solution.waysToBuyPensPencils(5, 10, 10));
}

}