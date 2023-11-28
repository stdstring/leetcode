#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSizeSubarray(std::vector<int> const &nums, int target) const
    {
        long long targetValue = target;
        std::unordered_map<long long, size_t> prefixSumMap;
        std::vector<long long> prefixSum(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            prefixSum[index] = nums[index] + (index > 0 ? prefixSum[index - 1] : 0);
            prefixSumMap.emplace(prefixSum[index], index);
        }
        const long long totalSum = prefixSum.back();
        int minSize = -1;
        const int fullRepeatedSize = static_cast<int>((targetValue / totalSum) * nums.size());
        targetValue = target % totalSum;
        if (targetValue == 0)
            return fullRepeatedSize;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            const long long prevPrefixSum = index > 0 ? prefixSum[index - 1] : 0;
            long long nextPrefixSum = prevPrefixSum + targetValue;
            if (nextPrefixSum > totalSum)
                nextPrefixSum -= totalSum;
            auto iterator = prefixSumMap.find(nextPrefixSum);
            if (iterator == prefixSumMap.cend())
                continue;
            int currentSize = static_cast<int>(iterator->second >= index ? iterator->second - index + 1 : nums.size() - index + iterator->second + 1) + fullRepeatedSize;
            minSize = std::min(currentSize, minSize == -1 ? INT_MAX : minSize);
        }
        return minSize;
    }
};

}

namespace MinSizeSubarrayInInfiniteArrayTask
{

TEST(MinSizeSubarrayInInfiniteArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minSizeSubarray({1, 2, 3}, 5));
    ASSERT_EQ(2, solution.minSizeSubarray({1, 1, 1, 2, 3}, 4));
    ASSERT_EQ(-1, solution.minSizeSubarray({2, 4, 6, 8}, 3));
}

TEST(MinSizeSubarrayInInfiniteArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.minSizeSubarray({2, 1, 5, 7, 7, 1, 6, 3}, 39));
}

}