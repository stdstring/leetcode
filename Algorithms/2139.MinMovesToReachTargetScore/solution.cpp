#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minMoves(int target, int maxDoubles) const
    {
        int movesCount = 0;
        while ((maxDoubles > 0) && (target > 1))
        {
            if (target % 2 == 0)
            {
                target /= 2;
                --maxDoubles;
            }
            else
                --target;
            ++movesCount;
        }
        return movesCount + (target - 1);
    }
};

}

namespace MinMovesToReachTargetScoreTask
{

TEST(MinMovesToReachTargetScoreTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minMoves(5, 0));
    ASSERT_EQ(7, solution.minMoves(19, 2));
    ASSERT_EQ(4, solution.minMoves(10, 4));
}

}