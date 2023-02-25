#include <cmath>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int arrangeCoins(int n) const
    {
        const long long discriminant = 1 + 8 * static_cast<long long>(n);
        return (static_cast<int>(sqrt(discriminant)) - 1) / 2;
    }
};

}

namespace ArrangingCoinsTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.arrangeCoins(5));
    ASSERT_EQ(3, solution.arrangeCoins(8));
}

}