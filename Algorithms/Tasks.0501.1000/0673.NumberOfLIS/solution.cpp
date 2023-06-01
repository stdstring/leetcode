#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findNumberOfLIS(std::vector<int> const &nums) const
    {
        size_t lisSize = 0;
        size_t lisCount = 0;
        std::vector<std::pair<size_t, size_t>> dp(nums.size(), {0, 0});
        for (size_t index = 0; index < nums.size(); ++index)
        {
            size_t currentSize = 0;
            size_t currentCount = 0;
            for (size_t prev = 0; prev < index; ++prev)
            {
                if (nums[prev] >= nums[index])
                    continue;
                if (currentSize == dp[prev].first)
                    currentCount += dp[prev].second;
                if (currentSize < dp[prev].first)
                {
                    currentSize = dp[prev].first;
                    currentCount = dp[prev].second;
                }
            }
            ++currentSize;
            if (currentCount == 0)
                currentCount = 1;
            dp[index] = {currentSize, currentCount};
            if (lisSize == currentSize)
                lisCount += currentCount;
            if (lisSize < currentSize)
            {
                lisSize = currentSize;
                lisCount = currentCount;
            }
        }
        return static_cast<int>(lisCount);
    }
};

}

namespace NumberOfLISTask
{

TEST(NumberOfLISTaskTests, Examples2)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findNumberOfLIS({1, 3, 5, 4, 7}));
    ASSERT_EQ(5, solution.findNumberOfLIS({2, 2, 2, 2, 2}));
}

}