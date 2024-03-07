#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumSum(std::vector<int> const &nums) const
    {
        std::vector<int> prefixMin(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
            prefixMin[index] = std::min(nums[index], index > 0 ? prefixMin[index - 1] : INT_MAX);
        std::vector<int> suffixMin(nums.size(), 0);
        for (size_t rIndex = 0; rIndex < nums.size(); ++rIndex)
        {
            const size_t index = nums.size() - 1 - rIndex;
            suffixMin[index] = std::min(nums[index], rIndex > 0 ? suffixMin[index + 1] : INT_MAX);
        }
        int minSum = -1;
        for (size_t index = 1; index < nums.size() - 1; ++index)
        {
            if (prefixMin[index - 1] >= nums[index])
                continue;
            if (suffixMin[index + 1] >= nums[index])
                continue;
            int currentSum = prefixMin[index - 1] + nums[index] + suffixMin[index + 1];
            minSum = std::min(currentSum, minSum == -1 ? INT_MAX : minSum);
        }
        return minSum;
    }
};

}

namespace MinSumOfMountainTriplets2Task
{

TEST(MinSumOfMountainTriplets2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.minimumSum({8, 6, 1, 5, 3}));
    ASSERT_EQ(13, solution.minimumSum({5, 4, 8, 7, 10, 2}));
    ASSERT_EQ(-1, solution.minimumSum({6, 5, 4, 3, 4, 5}));
}

}