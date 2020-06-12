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
        std::vector<int> indices;
        indices.reserve(nums.size());
        for (int index = 0; index < nums.size(); ++index)
        {
            indices.push_back(index);
        }
        std::sort(indices.begin(), indices.end(), [&nums](int left, int right){ return nums[left] < nums[right]; });
        // use two pointer approach
        int left = 0;
        int right = indices.size() - 1;
        while (left != right)
        {
            const int value = nums[indices[left]] + nums[indices[right]];
            if (value == target)
                return {indices[left], indices[right]};
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