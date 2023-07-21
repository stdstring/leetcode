#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSumAfterPartitioning(std::vector<int> const &arr, int k) const
    {
        const size_t maxSubarraySize = k;
        std::vector<int> dp(arr.size(), 0);
        for (size_t index = 0; index < arr.size(); ++index)
        {
            int maxItem = 0;
            for (size_t shift = 0; (shift < maxSubarraySize) && (index + shift) < arr.size(); ++shift)
            {
                maxItem = std::max(maxItem, arr[index + shift]);
                dp[index + shift] = std::max(dp[index + shift], (index == 0 ? 0 : dp[index - 1]) + maxItem * static_cast<int>(shift + 1));
            }
        }
        return dp.back();
    }
};

}

namespace PartitionArrayForMaxSumTask
{

TEST(PartitionArrayForMaxSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(84, solution.maxSumAfterPartitioning({1, 15, 7, 9, 2, 5, 10}, 3));
    ASSERT_EQ(83, solution.maxSumAfterPartitioning({1, 4, 1, 5, 7, 3, 6, 1, 9, 9, 3}, 4));
    ASSERT_EQ(1, solution.maxSumAfterPartitioning({1}, 1));
}

}