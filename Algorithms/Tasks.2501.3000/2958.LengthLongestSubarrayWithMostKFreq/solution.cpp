#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSubarrayLength(std::vector<int> const &nums, int k) const
    {
        const size_t maxFrequency = k;
        std::unordered_map<int, size_t> slidingWindowsData;
        size_t start = 0;
        size_t maxLength = 0;
        for (size_t end = 0; end < nums.size(); ++end)
        {
            int current = nums[end];
            auto currentIterator = slidingWindowsData.find(current);
            if (currentIterator == slidingWindowsData.end())
                currentIterator = slidingWindowsData.emplace(current, 0).first;
            ++currentIterator->second;
            while (currentIterator->second > maxFrequency)
            {
                const auto startIterator = slidingWindowsData.find(nums[start]);
                --startIterator->second;
                ++start;
            }
            maxLength = std::max(maxLength, end - start + 1);
        }
        return static_cast<int>(maxLength);
    }
};

}

namespace LengthLongestSubarrayWithMostKFreqTask
{

TEST(LengthLongestSubarrayWithMostKFreqTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.maxSubarrayLength({1, 2, 3, 1, 2, 3, 1, 2}, 2));
    ASSERT_EQ(2, solution.maxSubarrayLength({1, 2, 1, 2, 1, 2, 1, 2}, 1));
    ASSERT_EQ(4, solution.maxSubarrayLength({5, 5, 5, 5, 5, 5, 5}, 4));
}

}