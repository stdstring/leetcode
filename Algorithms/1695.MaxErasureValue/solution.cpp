#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumUniqueSubarray(std::vector<int> const &nums) const
    {
        constexpr int maxNumber = 10000;
        std::vector<bool> subarrayNumbers(maxNumber + 1, false);
        int subarraySum = 0;
        int maxSum = 0;
        for (size_t start = 0, end = 0; end < nums.size(); )
        {
            if (!subarrayNumbers[nums[end]])
            {
                subarrayNumbers[nums[end]] = true;
                subarraySum += nums[end];
                ++end;
                maxSum = std::max(maxSum, subarraySum);
            }
            else
            {
                subarrayNumbers[nums[start]] = false;
                subarraySum -= nums[start];
                ++start;
            }
        }
        return maxSum;
    }
};

}

namespace MaxErasureValueTask
{

TEST(MaxErasureValueTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(17, solution.maximumUniqueSubarray({4, 2, 4, 5, 6}));
    ASSERT_EQ(8, solution.maximumUniqueSubarray({5, 2, 1, 2, 5, 2, 1, 2, 5}));
}

}