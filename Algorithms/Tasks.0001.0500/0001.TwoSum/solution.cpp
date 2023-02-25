#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> const &nums, int target) const
    {
        // create and sort vector of indices
        std::vector<size_t> indices;
        indices.reserve(nums.size());
        for (size_t index = 0; index < nums.size(); ++index)
        {
            indices.push_back(index);
        }
        std::sort(indices.begin(), indices.end(), [&nums](size_t left, size_t right){ return nums[left] < nums[right]; });
        // use two pointer approach
        size_t left = 0;
        size_t right = indices.size() - 1;
        while (left != right)
        {
            const int value = nums[indices[left]] + nums[indices[right]];
            if (value == target)
                return {static_cast<int>(indices[left]), static_cast<int>(indices[right])};
            if (value < target)
                ++left;
            else if (value > target)
                --right;
        }
        return {};
    }
};

}

namespace TwoSumTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1}), solution.twoSum({2, 7, 11, 15}, 9));
}

TEST(TwoSumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2}), solution.twoSum({3, 2, 4}, 6));
}

}