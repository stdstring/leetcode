#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestEqualSubarray(std::vector<int> const &nums, int k) const
    {
        const size_t maxDelete = k;
        std::unordered_map<int, size_t> windowMap;
        size_t windowSize = 0;
        // prepare
        size_t start = 0;
        while (windowSize < nums.size())
        {
            ++windowMap[nums[windowSize]];
            ++windowSize;
            if ((windowSize - windowMap[nums[start]]) > maxDelete)
            {
                --windowSize;
                --windowMap[nums[windowSize]];
                break;
            }
        }
        // move
        size_t maxSize = windowMap[nums[start]];
        for (size_t end = windowSize; end < nums.size(); ++end)
        {
            ++windowMap[nums[end]];
            ++windowSize;
            while ((windowSize - windowMap[nums[start]]) > maxDelete)
            {
                --windowMap[nums[start]];
                --windowSize;
                ++start;
            }
            maxSize = std::max(maxSize, windowMap[nums[start]]);
        }
        while (start < nums.size())
        {
            if ((windowSize - windowMap[nums[start]]) <= maxDelete)
                maxSize = std::max(maxSize, windowMap[nums[start]]);
            --windowMap[nums[start]];
            --windowSize;
            ++start;
        }
        return static_cast<int>(maxSize);
    }
};

}

namespace FindLongestEqualSubarrayTask
{

TEST(FindLongestEqualSubarrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.longestEqualSubarray({1, 3, 2, 3, 1, 3}, 3));
    ASSERT_EQ(4, solution.longestEqualSubarray({1, 1, 2, 2, 1, 1}, 2));
}

TEST(FindLongestEqualSubarrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.longestEqualSubarray({3, 1, 1}, 2));
}

}