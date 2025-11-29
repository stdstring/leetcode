#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxSubarraySum(std::vector<int> const &nums, int k) const
    {
        std::vector<long long> kSum(k, std::numeric_limits<long long>::max() / 2);
        // kSum[k-1] = 0 for taking into account subarrays starting at index 0 whose lengths are divisible by k.
        kSum.back() = 0;
        long long maxSum = std::numeric_limits<long long>::min();
        long long prefixSum = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            prefixSum += nums[index];
            const size_t rest = index % k;
            const long long currentSubarraySum = prefixSum - kSum[rest];
            kSum[rest] = std::min(kSum[rest], prefixSum);
            if (index >= (kSum.size() - 1))
                maxSum = std::max(maxSum, currentSubarraySum);
        }
        return maxSum;
    }
};

}

namespace MaxSubarraySumWithLengthDivisibleByKTask
{

TEST(MaxSubarraySumWithLengthDivisibleByKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxSubarraySum({1, 2}, 1));
    ASSERT_EQ(-10, solution.maxSubarraySum({-1, -2, -3, -4, -5}, 4));
    ASSERT_EQ(4, solution.maxSubarraySum({-5, 1, 2, -3, 4}, 2));
}

TEST(MaxSubarraySumWithLengthDivisibleByKTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxSubarraySum({9, -11, 15}, 2));
}

}