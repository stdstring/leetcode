#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxBottlesDrunk(int numBottles, int numExchange) const
    {
        int bottlesDrunk = 0;
        int emptyBottles = 0;
        while (numBottles > 0)
        {
            bottlesDrunk += numBottles;
            emptyBottles += numBottles;
            numBottles = 0;
            for (; numExchange <= emptyBottles; ++numExchange)
            {
                emptyBottles -= numExchange;
                ++numBottles;
            }
        }
        return bottlesDrunk;
    }
};

}

namespace WaterBottles2Task
{

TEST(WaterBottles2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.maxBottlesDrunk(13, 6));
    ASSERT_EQ(13, solution.maxBottlesDrunk(10, 3));
}

}