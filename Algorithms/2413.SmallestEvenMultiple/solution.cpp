#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int smallestEvenMultiple(int n) const
    {
        return n % 2 == 0 ? n : 2 * n;
    }
};

}

namespace SmallestEvenMultipleTask
{

TEST(SmallestEvenMultipleTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(10, solution.smallestEvenMultiple(5));
    ASSERT_EQ(6, solution.smallestEvenMultiple(6));
}

}
