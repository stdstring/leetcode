#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double largestSumOfAverages(std::vector<int> const &nums, int k) const
    {
        const size_t maxSubarrays = k;
        // init
        std::vector<int> prefixSum(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
            prefixSum[index] = (index > 0 ? prefixSum[index - 1] : 0) + nums[index];
        std::vector<double> dpCurrent(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
            dpCurrent[index] = static_cast<double>(prefixSum[index]) / static_cast<int>(index + 1);
        double bestSum = dpCurrent.back();
        // process
        for (size_t subarrayCount = 2; subarrayCount <= maxSubarrays; ++subarrayCount)
        {
            std::vector<double> dpNext(nums.size(), 0);
            for (size_t startIndex = subarrayCount - 1; startIndex < nums.size(); ++startIndex)
            {
                for (size_t endIndex = startIndex; endIndex < nums.size(); ++endIndex)
                {
                    const double currentSum = static_cast<double>(prefixSum[endIndex] - prefixSum[startIndex - 1]) / static_cast<int>(endIndex - startIndex + 1);
                    dpNext[endIndex] = std::max(dpNext[endIndex], dpCurrent[startIndex - 1] + currentSum);
                }
            }
            std::swap(dpCurrent, dpNext);
            bestSum = std::max(bestSum, dpCurrent.back());
        }
        return bestSum;
    }
};

}

namespace LargestSumOfAveragesTask
{

TEST(LargestSumOfAveragesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_DOUBLE_EQ(20.00000, solution.largestSumOfAverages({9, 1, 2, 3, 9}, 3));
    ASSERT_DOUBLE_EQ(20.50000, solution.largestSumOfAverages({1, 2, 3, 4, 5, 6, 7}, 4));
}

}