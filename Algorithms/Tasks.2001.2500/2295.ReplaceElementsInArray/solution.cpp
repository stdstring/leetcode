#include <vector>

#include "gtest/gtest.h"

namespace
{
class Solution
{
public:
    [[nodiscard]] std::vector<int> arrayChange(std::vector<int> const &nums, std::vector<std::vector<int>> const &operations) const
    {
        constexpr int maxValue = 1000000;
        std::vector<int> result(nums);
        std::vector<size_t> indices(maxValue + 1, nums.size());
        for (size_t index = 0; index < nums.size(); ++index)
            indices[nums[index]] = index;
        for (std::vector<int> const &operation : operations)
        {
            const size_t index = indices[operation[0]];
            indices[operation[0]] = result.size();
            indices[operation[1]] = index;
            result[index] = operation[1];
        }
        return result;
    }
};

}

namespace ReplaceElementsInArrayTask
{

TEST(ReplaceElementsInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 2, 7, 1}), solution.arrayChange({1, 2, 4, 6}, {{1, 3}, {4, 7}, {6, 1}}));
    ASSERT_EQ(std::vector<int>({2, 1}), solution.arrayChange({1, 2}, {{1, 3}, {2, 1}, {3, 2}}));
}

}