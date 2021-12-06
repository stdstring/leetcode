#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minCostToMoveChips(std::vector<int> const &position) const
    {
        size_t evenPositions = 0;
        size_t oddPositions = 0;
        for (const int chip : position)
            ++(chip % 2 == 0 ? evenPositions : oddPositions);
        return static_cast<int>(std::min(evenPositions, oddPositions));
    }
};

}

namespace MinCostToMoveChipsToSamePositionTask
{

TEST(MinCostToMoveChipsToSamePositionTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.minCostToMoveChips({1, 2, 3}));
    ASSERT_EQ(2, solution.minCostToMoveChips({2, 2, 2, 3, 3}));
    ASSERT_EQ(1, solution.minCostToMoveChips({1, 1000000000}));
}

}