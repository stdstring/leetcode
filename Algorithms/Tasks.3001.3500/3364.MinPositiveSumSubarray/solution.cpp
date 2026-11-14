#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumSumSubarray(std::vector<int> const &nums, int l, int r) const
    {
        std::vector<int> prefixSum(nums.size() + 1, 0);
        for (size_t index = 0; index < nums.size(); ++index)
            prefixSum[index + 1] = nums[index] + prefixSum[index];
        const size_t minSize = l;
        const size_t maxSize = r;
        int result = INT_MAX;
        for (size_t start = 0; start <= nums.size() - minSize; ++start)
        {
            for (size_t currentSize = minSize; ((start + currentSize) <= nums.size()) && (currentSize <= maxSize); ++currentSize)
            {
                const int currentSum = prefixSum[start + currentSize] - prefixSum[start] ;
                if (currentSum > 0)
                    result = std::min(result, currentSum);
            }
        }
        return result == INT_MAX ? -1 : result;
    }
};

}

namespace MinPositiveSumSubarrayTask
{

TEST(MinPositiveSumSubarrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minimumSumSubarray({3, -2, 1, 4}, 2, 3));
    ASSERT_EQ(-1, solution.minimumSumSubarray({-2, 2, -3, 1}, 2, 3));
    ASSERT_EQ(3, solution.minimumSumSubarray({1, 2, 3, 4}, 2, 4));
}

TEST(MinPositiveSumSubarrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(10, solution.minimumSumSubarray({7, 3}, 2, 2));
}

}