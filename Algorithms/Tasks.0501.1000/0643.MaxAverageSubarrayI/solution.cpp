#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double findMaxAverage(std::vector<int> const &nums, int k) const
    {
        int maxSum = std::accumulate(nums.cbegin(), nums.cbegin() + k, 0);
        int currentSum = maxSum;
        for (size_t index = 1; index <= nums.size() - k; ++index)
        {
            int nextSum = currentSum - nums[index - 1] + nums[index + k - 1];
            maxSum = std::max(maxSum, nextSum);
            currentSum = nextSum;
        }
        return 1.0 * maxSum / k;
    }
};

}

namespace MaxAverageSubarrayITask
{

TEST(MaxAverageSubarrayITaskTests, Examples)
{
    const Solution solution;
    ASSERT_DOUBLE_EQ(12.75, solution.findMaxAverage({1, 12, -5, -6, 50, 3}, 4));
    ASSERT_DOUBLE_EQ(5.0, solution.findMaxAverage({5}, 1));
}

}