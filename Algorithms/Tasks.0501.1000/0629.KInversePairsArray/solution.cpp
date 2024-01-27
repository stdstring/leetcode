#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int kInversePairs(int n, int k) const
    {
        // f(n,k) = f(n-1,k) + f(n-1,k-1) + f(n-1,k-2) + ... + f(n-1,k-n+1)
        // where f(n,0) = 1. f(n,k) = 0 if n <= 0 or k < 0 except for (n,k)=(0,0).
        if (k == 0)
            return 1;
        constexpr int modValue = 1000000007;
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
        dp[0][0] = 1;
        for (int number = 1; number <= n; ++number)
        {
            long long currentValue = 0;
            for (int inversePairs = 0; inversePairs <= k; ++inversePairs)
            {
                currentValue += dp[number - 1][inversePairs];
                if (inversePairs >= number)
                    currentValue -= dp[number - 1][inversePairs - number];
                dp[number][inversePairs] = static_cast<int>(currentValue % modValue);
            }
        }
        return dp.back().back();
    }
};

}

namespace KInversePairsArrayTask
{

TEST(KInversePairsArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.kInversePairs(3, 0));
    ASSERT_EQ(2, solution.kInversePairs(3, 1));
}

TEST(KInversePairsArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.kInversePairs(3, 3));
}

}