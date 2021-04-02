#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool canPartition(std::vector<int> const &nums) const
    {
        const int totalSum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if (totalSum % 2 == 1)
            return false;
        const int equalSubsetSum = totalSum / 2;
        std::vector<bool> subsetSums(1 + static_cast<size_t>(equalSubsetSum), false);
        int maxSubsetSum = 0;
        for (int number : nums)
        {
            if (number == equalSubsetSum)
                return true;
            if (number > equalSubsetSum)
                continue;
            for (int sum = maxSubsetSum; sum > 0; --sum)
            {
                if (subsetSums[sum] && (sum + number) <= equalSubsetSum)
                {
                    const int resultSum = sum + number;
                    subsetSums[resultSum] = true;
                    maxSubsetSum = std::max(maxSubsetSum, resultSum);
                }
            }
            subsetSums[number] = true;
            maxSubsetSum = std::max(maxSubsetSum, number);
            if (maxSubsetSum == equalSubsetSum)
                return true;
        }
        return false;
    }
};

}

namespace PartitionEqualSubsetSumTask
{

TEST(PartitionEqualSubsetSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canPartition({1, 5, 11, 5}));
    ASSERT_EQ(false, solution.canPartition({1, 2, 3, 5}));
}

TEST(PartitionEqualSubsetSumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.canPartition({1, 2, 5}));
    ASSERT_EQ(true, solution.canPartition({2, 2, 1, 1}));
}

}