#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countGoodStrings(int low, int high, int zero, int one) const
    {
        constexpr int modValue = 1000000007;
        std::vector<int> dp(high + 1, 0);
        dp[0] = 1;
        for (int index = 0; index <= high; ++index)
        {
            if ((index + zero) <= high)
                dp[index + zero] = (dp[index + zero] + dp[index]) % modValue;
            if ((index + one) <= high)
                dp[index + one] = (dp[index + one] + dp[index]) % modValue;
        }
        int result = 0;
        for (int index = low; index <= high; ++index)
            result = (result + dp[index]) % modValue;
        return result;
    }
};

}

namespace CountWaysToBuildGoodStringsTask
{

TEST(CountWaysToBuildGoodStringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.countGoodStrings(3, 3, 1, 1));
    ASSERT_EQ(5, solution.countGoodStrings(2, 3, 1, 2));
}

}