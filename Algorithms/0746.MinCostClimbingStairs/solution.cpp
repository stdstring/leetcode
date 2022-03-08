#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minCostClimbingStairs(std::vector<int> const &cost) const
    {
        int currentCost = 0;
        int next1Cost = 0;
        int next2Cost = INT_MAX;
        for (const int value : cost)
        {
            next1Cost = std::min(next1Cost, currentCost + value);
            next2Cost = std::min(next2Cost, currentCost + value);
            currentCost = next1Cost;
            next1Cost = next2Cost;
            next2Cost = INT_MAX;
        }
        return currentCost;
    }
};

}

namespace MinCostClimbingStairsTask
{

TEST(MinCostClimbingStairsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(15, solution.minCostClimbingStairs({10, 15, 20}));
    ASSERT_EQ(6, solution.minCostClimbingStairs({1, 100, 1, 1, 1, 100, 1, 1, 100, 1}));
}

}