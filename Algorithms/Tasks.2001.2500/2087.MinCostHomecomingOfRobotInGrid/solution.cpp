#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minCost(std::vector<int> const &startPos, std::vector<int> const &homePos, std::vector<int> const &rowCosts, std::vector<int> const &colCosts) const
    {
        int totalCost = 0;
        const int horizontalShift = std::abs(startPos[0] - homePos[0]);
        const int horizontalDelta = calcDelta(startPos[0], homePos[0]);
        const int verticalShift = std::abs(startPos[1] - homePos[1]);
        const int verticalDelta = calcDelta(startPos[1], homePos[1]);
        for (int shift = 1; shift <= horizontalShift; ++shift)
            totalCost += rowCosts[startPos[0] + horizontalDelta * shift];
        for (int shift = 1; shift <= verticalShift; ++shift)
            totalCost += colCosts[startPos[1] + verticalDelta * shift];
        return totalCost;
    }

private:
    [[nodiscard]] int calcDelta(int sourceCoord, int destCoord) const
    {
        return sourceCoord < destCoord ? 1 : (sourceCoord == destCoord ? 0 : -1);
    }
};

}

namespace MinCostHomecomingOfRobotInGridTask
{

TEST(MinCostHomecomingOfRobotInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(18, solution.minCost({1, 0}, {2, 3}, {5, 4, 3}, {8, 2, 6, 7}));
    ASSERT_EQ(0, solution.minCost({0, 0}, {0, 0}, {5}, {26}));
}

}