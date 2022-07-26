#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isSameAfterReversals(int num) const
    {
        return num == 0 || ((num % 10) != 0);
    }
};

}

namespace NumberAfterDoubleReversalTask
{

TEST(NumberAfterDoubleReversalTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isSameAfterReversals(526));
    ASSERT_EQ(false, solution.isSameAfterReversals(1800));
    ASSERT_EQ(true, solution.isSameAfterReversals(0));
}

}