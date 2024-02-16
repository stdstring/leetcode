#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maximumSubarraySum(std::vector<int> const &nums, int k) const
    {
        std::unordered_map<int, long long> prefixSumMap;
        long long prefixSum = 0;
        long long maxSum = LLONG_MIN;
        for (int number : nums)
        {
            const long long currentPrefixSum = prefixSum + number;
            if (prefixSumMap.contains(number - k))
                maxSum = std::max(maxSum, currentPrefixSum - prefixSumMap[number - k]);
            if (prefixSumMap.contains(number + k))
                maxSum = std::max(maxSum, currentPrefixSum - prefixSumMap[number + k]);
            auto numberIterator = prefixSumMap.find(number);
            if (numberIterator == prefixSumMap.end())
                prefixSumMap.emplace(number, prefixSum);
            else
                numberIterator->second = std::min(numberIterator->second, prefixSum);
            prefixSum = currentPrefixSum;
        }
        return maxSum == LLONG_MIN ? 0 : maxSum;
    }
};

}

namespace MaxGoodSubarraySumTask
{

TEST(MaxGoodSubarraySumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(11, solution.maximumSubarraySum({1, 2, 3, 4, 5, 6}, 1));
    ASSERT_EQ(11, solution.maximumSubarraySum({-1, 3, 2, 4, 5}, 3));
    ASSERT_EQ(-6, solution.maximumSubarraySum({-1, -2, -3, -4}, 2));
}

TEST(MaxGoodSubarraySumTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.maximumSubarraySum({1, 5}, 2));
}

}