#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxAscendingSum(std::vector<int> const &nums) const
    {
        int maxSum = 0;
        int currentSum = 0;
        int prevValue = 0;
        for (int num : nums)
        {
            if (num > prevValue)
            {
                prevValue = num;
                currentSum += num;
            }
            else
            {
                maxSum = std::max(maxSum, currentSum);
                currentSum = prevValue = num;
            }
        }
        return std::max(maxSum, currentSum);
    }
};

}

namespace MaximumAscendingSubarraySumTask
{

TEST(MaximumAscendingSubarraySumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(65, solution.maxAscendingSum({10, 20, 30, 5, 10, 50}));
    ASSERT_EQ(150, solution.maxAscendingSum({10, 20, 30, 40, 50}));
    ASSERT_EQ(33, solution.maxAscendingSum({12, 17, 15, 13, 10, 11, 12}));
    ASSERT_EQ(100, solution.maxAscendingSum({100, 10, 1}));
}

}