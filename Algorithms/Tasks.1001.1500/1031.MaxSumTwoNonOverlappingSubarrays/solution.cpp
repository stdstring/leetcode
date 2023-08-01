#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSumTwoNoOverlap(std::vector<int> const &nums, int firstLen, int secondLen) const
    {
        const size_t firstSize = firstLen;
        const size_t secondSize = secondLen;
        std::vector<int> bestFirstPrefix(nums.size(), 0);
        int prefixSum = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            prefixSum += nums[index];
            if (index >= firstSize)
                prefixSum -= nums[index - firstSize];
            if (index >= (firstSize - 1))
                bestFirstPrefix[index] = std::max(prefixSum, index > 0 ? bestFirstPrefix[index - 1] : 0);
        }
        std::vector<int> bestFirstSuffix(nums.size(), 0);
        int suffixSum = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            const size_t rIndex = nums.size() - 1 - index;
            suffixSum += nums[rIndex];
            if (index >= firstSize)
                suffixSum -= nums[rIndex + firstSize];
            if (index >= (firstSize - 1))
                bestFirstSuffix[rIndex] = std::max(suffixSum, index > 0 ? bestFirstSuffix[rIndex + 1] : 0);
        }
        int bestSum = 0;
        int secondSum = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            secondSum += nums[index];
            if (index >= secondSize)
                secondSum -= nums[index - secondSize];
            if (index >= (firstSize + secondSize - 1))
                bestSum = std::max(bestSum, secondSum + bestFirstPrefix[index - secondSize]);
            if ((index >= (secondSize - 1)) && (index < (nums.size() - firstSize)))
                bestSum = std::max(bestSum, secondSum + bestFirstSuffix[index + 1]);
        }
        return bestSum;
    }
};

}

namespace MaxSumTwoNonOverlappingSubarraysTask
{

TEST(MaxSumTwoNonOverlappingSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(20, solution.maxSumTwoNoOverlap({0, 6, 5, 2, 2, 5, 1, 9, 4}, 1, 2));
    ASSERT_EQ(29, solution.maxSumTwoNoOverlap({3, 8, 1, 3, 2, 1, 8, 9, 0}, 3, 2));
    ASSERT_EQ(31, solution.maxSumTwoNoOverlap({2, 1, 5, 6, 0, 9, 5, 0, 3, 8}, 4, 3));
}

}