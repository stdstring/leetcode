#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int climbStairs(int n, std::vector<int> const &costs) const
    {
        std::vector<int> dp(n, INT_MAX);
        dp[0] = costs[0] + 1;
        if (n > 1)
            dp[1] = costs[1] + 4;
        if (n > 2)
            dp[2] = costs[2] + 9;
        for (int step = 0; step < n; ++step)
        {
            if ((step + 1) < n)
                dp[step + 1] = std::min(dp[step + 1], dp[step] + costs[step + 1] + 1);
            if ((step + 2) < n)
                dp[step + 2] = std::min(dp[step + 2], dp[step] + costs[step + 2] + 4);
            if ((step + 3) < n)
                dp[step + 3] = std::min(dp[step + 3], dp[step] + costs[step + 3] + 9);
        }
        return dp.back();
    }
};

}

namespace ClimbingStairs2Task
{

TEST(ClimbingStairs2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.climbStairs(4, {1, 2, 3, 4}));
    ASSERT_EQ(11, solution.climbStairs(4, {5, 1, 6, 2}));
    ASSERT_EQ(12, solution.climbStairs(3, {9, 8, 3}));
}

}