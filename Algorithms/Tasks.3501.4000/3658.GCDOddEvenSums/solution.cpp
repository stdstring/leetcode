#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int gcdOfOddEvenSums(int n) const
    {
        // arithmetic progression sum: S = n * (a1 + an) / 2
        // odd numbers: 1, 3, ..., 2 * n - 1
        // sum of odd numbers Sodd = n * (1 + 2 * n - 1) / 2 = n * n
        // even numbers: 2, 4, ..., 2 * n
        // sum of even numbers Seven = n * (2 + 2 * n) / 2 = n * (n + 1)
        // gcd(n * n, n * (n + 1)) = n * gcd(n, n + 1) = n
        // gcd(n, n + 1) = 1
        return n;
    }
};

}

namespace GCDOddEvenSumsTask
{

TEST(GCDOddEvenSumsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.gcdOfOddEvenSums(4));
    ASSERT_EQ(5, solution.gcdOfOddEvenSums(5));
}

}