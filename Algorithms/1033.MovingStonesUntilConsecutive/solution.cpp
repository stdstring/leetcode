#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> numMovesStones(int a, int b, int c) const
    {
        int left = a, middle = b, right = c;
        if (right < left)
            std::swap(left, right);
        if (right < middle)
            std::swap(right, middle);
        if (middle < left)
            std::swap(left, middle);
        const int minDelta = std::min(middle - left - 1, right - middle - 1);
        const int maxDelta = std::max(middle - left - 1, right - middle - 1);
        if ((minDelta == 0) && (maxDelta == 0))
            return {0, 0};
        return {minDelta == 0 || minDelta == 1 ? 1 : 2, minDelta + maxDelta};
    }
};

}

namespace MovingStonesUntilConsecutiveTask
{

TEST(MovingStonesUntilConsecutiveTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2}), solution.numMovesStones(1, 2, 5));
    ASSERT_EQ(std::vector<int>({0, 0}), solution.numMovesStones(4, 3, 2));
    ASSERT_EQ(std::vector<int>({1, 2}), solution.numMovesStones(3, 5, 1));
}

}