#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfWays(int n, int x) const
    {
        constexpr int moduloValue = 1000000007;
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int number = 1; number <= n; ++number)
        {
            int powerValue = power(number, x);
            if (powerValue > n)
                break;
            for (int sum = n - powerValue; sum >= 0; --sum)
            {
                if (dp[sum] != 0)
                    dp[sum + powerValue] = (dp[sum + powerValue] + dp[sum]) % moduloValue;
            }
        }
        return dp.back();
    }

private:
    [[nodiscard]] int power(int base, int pow) const
    {
        int result = 1;
        for (int step = 1; step <= pow; ++step)
            result *= base;
        return result;
    }
};

}

namespace WaysExpressIntegerAsPowersSumTask
{

TEST(WaysExpressIntegerAsPowersSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numberOfWays(10, 2));
    ASSERT_EQ(2, solution.numberOfWays(4, 1));
}

}