#include <algorithm>
#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestSubarray(std::vector<int> const &nums, int limit) const
    {
        size_t longestSize = 1;
        std::multiset<int> slidingWindow;
        for (size_t start = 0, end = 0; end < nums.size(); ++end)
        {
            slidingWindow.emplace(nums[end]);
            while ((*slidingWindow.crbegin() - *slidingWindow.cbegin()) > limit)
            {
                const auto iterator = slidingWindow.find(nums[start]);
                slidingWindow.erase(iterator);
                ++start;
            }
            longestSize = std::max(longestSize, end - start + 1);
        }
        return static_cast<int>(longestSize);
    }
};

}

namespace LongestContSubarrayAbsDiffLTELimitTask
{

TEST(LongestContSubarrayAbsDiffLTELimitTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.longestSubarray({8, 2, 4, 7}, 4));
    ASSERT_EQ(4, solution.longestSubarray({10, 1, 2, 4, 7, 2}, 5));
    ASSERT_EQ(3, solution.longestSubarray({4, 2, 2, 2, 4, 4, 2, 2}, 0));
}

}