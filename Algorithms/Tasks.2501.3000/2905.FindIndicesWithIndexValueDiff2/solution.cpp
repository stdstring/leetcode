#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findIndices(std::vector<int> const &nums, int indexDifference, int valueDifference) const
    {
        // pairs value - index
        std::vector<std::pair<int, size_t>> suffixMin(nums.size());
        std::vector<std::pair<int, size_t>> suffixMax(nums.size());
        for (size_t rIndex = 0; rIndex < nums.size(); ++rIndex)
        {
            size_t index = nums.size() - 1 - rIndex;
            if ((rIndex == 0) || (nums[index] < suffixMin[index + 1].first))
                suffixMin[index] = {nums[index], index};
            else
                suffixMin[index] = suffixMin[index + 1];
            if ((rIndex == 0) || (nums[index] > suffixMax[index + 1].first))
                suffixMax[index] = {nums[index], index};
            else
                suffixMax[index] = suffixMax[index + 1];
        }
        for (size_t start = 0, end = start + indexDifference; end < nums.size(); ++start, ++end)
        {
            if (std::abs(nums[start] - suffixMin[end].first) >= valueDifference)
                return {static_cast<int>(start), static_cast<int>(suffixMin[end].second)};
            if (std::abs(nums[start] - suffixMax[end].first) >= valueDifference)
                return {static_cast<int>(start), static_cast<int>(suffixMax[end].second)};
        }
        return {-1, -1};
    }
};

}

namespace FindIndicesWithIndexValueDiff2Task
{

TEST(FindIndicesWithIndexValueDiff2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 3}), solution.findIndices({5, 1, 4, 1}, 2, 4));
    ASSERT_EQ(std::vector<int>({0, 1}), solution.findIndices({2, 1}, 0, 0));
    ASSERT_EQ(std::vector<int>({-1, -1}), solution.findIndices({1, 2, 3}, 2, 4));
}

}