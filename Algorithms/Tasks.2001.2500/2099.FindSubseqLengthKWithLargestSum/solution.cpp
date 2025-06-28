#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> maxSubsequence(std::vector<int> const &nums, int k) const
    {
        std::vector<size_t> indexes(nums.size(), 0);
        std::iota(indexes.begin(), indexes.end(), 0);
        std::ranges::sort(indexes, [&nums](size_t left, size_t right){ return nums[left] > nums[right]; });
        std::sort(indexes.begin(), std::next(indexes.begin(), k));
        std::vector<int> result;
        for (auto iterator = indexes.begin(); iterator != std::next(indexes.begin(), k); ++iterator)
            result.emplace_back(nums[*iterator]);
        return result;
    }
};

}

namespace FindSubseqLengthKWithLargestSumTask
{

TEST(FindSubseqLengthKWithLargestSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 3}), solution.maxSubsequence({2, 1, 3, 3}, 2));
    ASSERT_EQ(std::vector<int>({-1, 3, 4}), solution.maxSubsequence({-1, -2, 3, 4}, 3));
    ASSERT_EQ(std::vector<int>({3, 4}), solution.maxSubsequence({3, 4, 3, 3}, 2));
}

}