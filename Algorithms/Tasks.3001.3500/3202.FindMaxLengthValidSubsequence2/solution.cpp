#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumLength(std::vector<int> const &nums, int k) const
    {
        // (sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k
        // so sub[0] % k == sub[2] % k == ... and sub[1] % k == sub[3] % k == ...
        std::vector<std::vector<int>> dp(k, std::vector<int>(k, 0));
        int maxLength = 0;
        for (const int number : nums)
        {
            const int current = number % k;
            for (int prev = 0; prev < k; ++prev)
            {
                dp[prev][current] = dp[current][prev] + 1;
                maxLength = std::max(maxLength, dp[prev][current]);
            }
        }
        return maxLength;
    }
};

}

namespace FindMaxLengthValidSubsequence2Task
{

TEST(FindMaxLengthValidSubsequence2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.maximumLength({1, 2, 3, 4, 5}, 2));
    ASSERT_EQ(4, solution.maximumLength({1, 4, 2, 3, 1, 4}, 3));
}

}