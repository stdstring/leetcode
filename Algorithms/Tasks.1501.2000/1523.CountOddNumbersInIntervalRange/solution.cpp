#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countOdds(int low, int high) const
    {
        const int delta = high - low;
        return (low % 2 == 1) + (delta / 2) + (low % 2 == 0 ? delta % 2 : 0);
    }
};

}

namespace CountOddNumbersInIntervalRangeTask
{

TEST(CountOddNumbersInIntervalRangeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.countOdds(3, 7));
    ASSERT_EQ(1, solution.countOdds(8, 10));
}

}