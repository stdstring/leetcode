#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSubarraySumCircular(std::vector<int> const &nums) const
    {
        // used modification of Kadane’s algorithm
        int minSum = nums[0];
        int maxSum = nums[0];
        int currentMinSum = 0;
        int currentMaxSum = 0;
        int totalSum = 0;
        for (const int number : nums)
        {
            currentMinSum = std::min(currentMinSum, 0) + number;
            currentMaxSum = std::max(currentMaxSum, 0) + number;
            minSum = std::min(minSum, currentMinSum);
            maxSum = std::max(maxSum, currentMaxSum);
            totalSum += number;
        }
        return minSum == totalSum ? maxSum : std::max(maxSum, totalSum - minSum);
    }
};

}

namespace MaxSumCircularSubarrayTask
{

TEST(MaxSumCircularSubarrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxSubarraySumCircular({1, -2, 3, -2}));
    ASSERT_EQ(10, solution.maxSubarraySumCircular({5, -3, 5}));
    ASSERT_EQ(-2, solution.maxSubarraySumCircular({-3, -2, -3}));
}

}