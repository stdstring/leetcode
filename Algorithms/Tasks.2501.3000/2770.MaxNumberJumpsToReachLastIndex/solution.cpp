#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumJumps(std::vector<int> const &nums, int target) const
    {
        std::vector<size_t> dp(nums.size(), INT_MAX);
        dp[0] = 0;
        for (size_t fromIndex = 0; fromIndex < nums.size() - 1; ++fromIndex)
        {
            if (dp[fromIndex] == INT_MAX)
                continue;
            for (size_t toIndex = fromIndex + 1; toIndex < nums.size(); ++toIndex)
            {
                if (std::abs(nums[toIndex] - nums[fromIndex]) <= target)
                    dp[toIndex] = std::max((dp[toIndex] == INT_MAX) ? 0 : dp[toIndex], dp[fromIndex] + 1);
            }
        }
        return (dp.back() == INT_MAX) ? - 1 : static_cast<int>(dp.back());
    }
};

}

namespace MaxNumberJumpsToReachLastIndexTask
{

TEST(MaxNumberJumpsToReachLastIndexTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumJumps({1, 3, 6, 4, 1, 2}, 2));
    ASSERT_EQ(5, solution.maximumJumps({1, 3, 6, 4, 1, 2}, 3));
    ASSERT_EQ(-1, solution.maximumJumps({1, 3, 6, 4, 1, 2}, 0));
}

}