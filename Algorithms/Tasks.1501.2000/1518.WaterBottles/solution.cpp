#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numWaterBottles(int numBottles, int numExchange) const
    {
        int totalDrink = 0;
        int fullBottles = numBottles;
        int emptyBottles = 0;
        while (fullBottles > 0)
        {
            totalDrink += fullBottles;
            emptyBottles += fullBottles;
            fullBottles = emptyBottles / numExchange;
            emptyBottles %= numExchange;
        }
        return totalDrink;
    }
};

}

namespace WaterBottlesTask
{

TEST(WaterBottlesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.numWaterBottles(9, 3));
    ASSERT_EQ(19, solution.numWaterBottles(15, 4));
}

}