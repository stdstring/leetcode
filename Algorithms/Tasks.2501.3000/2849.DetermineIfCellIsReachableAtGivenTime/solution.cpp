#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) const
    {
        const int deltaX = std::abs(sx - fx);
        const int deltaY = std::abs(sy - fy);
        if ((deltaX == 0) && (deltaY == 0))
            return t != 1;
        return std::max(deltaX, deltaY) <= t;
    }
};

}

namespace DetermineIfCellIsReachableAtGivenTimeTask
{

TEST(DetermineIfCellIsReachableAtGivenTimeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isReachableAtTime(2, 4, 7, 7, 6));
    ASSERT_EQ(false, solution.isReachableAtTime(3, 1, 7, 3, 3));
}

TEST(DetermineIfCellIsReachableAtGivenTimeTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isReachableAtTime(2, 4, 2, 4, 0));
    ASSERT_EQ(false, solution.isReachableAtTime(2, 4, 2, 4, 1));
    ASSERT_EQ(true, solution.isReachableAtTime(2, 4, 2, 4, 2));
    ASSERT_EQ(true, solution.isReachableAtTime(2, 4, 2, 4, 3));
}

}