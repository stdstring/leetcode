#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> targetIndices(std::vector<int> const &nums, int target) const
    {
        std::vector<int> sortedNums(nums);
        std::ranges::sort(sortedNums);
        std::vector<int> result;
        size_t index = 0;
        while ((index < sortedNums.size()) && (sortedNums[index] < target))
            ++index;
        for (; (index < sortedNums.size()) && (sortedNums[index] == target); ++index)
            result.emplace_back(static_cast<int>(index));
        return result;
    }
};

}

namespace FindTargetIndicesAfterSortingArrayTask
{

TEST(FindTargetIndicesAfterSortingArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2}), solution.targetIndices({1, 2, 5, 2, 3}, 2));
    ASSERT_EQ(std::vector<int>({3}), solution.targetIndices({1, 2, 5, 2, 3}, 3));
    ASSERT_EQ(std::vector<int>({4}), solution.targetIndices({1, 2, 5, 2, 3}, 5));
}

}