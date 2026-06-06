#include <cmath>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> leftRightDifference(std::vector<int> const &nums) const
    {
        std::vector<int> leftSum(nums.size(), 0);
        std::vector<int> rightSum(nums.size(), 0);
        for (size_t index = 1; index < nums.size(); ++index)
        {
            const size_t rIndex = nums.size() - 1 - index;
            leftSum[index] = leftSum[index - 1] + nums[index - 1];
            rightSum[rIndex] = rightSum[rIndex + 1] + nums[rIndex + 1];
        }
        std::vector<int> result(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            result[index] = std::abs(leftSum[index] - rightSum[index]);
        }
        return result;
    }
};

}

namespace LeftRightSumDifferencesTask
{

TEST(LeftRightSumDifferencesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({15, 1, 11, 22}), solution.leftRightDifference({10, 4, 8, 3}));
    ASSERT_EQ(std::vector<int>({0}), solution.leftRightDifference({1}));
}

}