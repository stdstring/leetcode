#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool canPartitionKSubsets(std::vector<int> const &nums, int k) const
    {
        const int totalSum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if ((totalSum % k) != 0)
            return false;
        const int portionSum = totalSum / k;
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end(), std::greater<>());
        if (numbers.front() > portionSum)
            return false;
        int usedNumbersMask = (1 << nums.size()) - 1;
        while (usedNumbersMask != 0)
        {
            const int nextUsedNumbersMask = tryCreateSubset(numbers, portionSum, usedNumbersMask);
            if (usedNumbersMask == nextUsedNumbersMask)
                return false;
            usedNumbersMask = nextUsedNumbersMask;
        }
        return true;
    }

private:
    int tryCreateSubset(std::vector<int> const &numbers, int portionSum, int usedNumbersMask) const
    {
        int initUsedNumbersMask = usedNumbersMask;
        size_t index = 0;
        while ((usedNumbersMask & (1 << index)) == 0)
            ++index;
        usedNumbersMask &= ~(1 << index);
        portionSum -= numbers[index];
        if (portionSum == 0)
            return usedNumbersMask;
        int nextUsedNumbersMask = tryCreateSubset(numbers, portionSum, usedNumbersMask, index + 1);
        return nextUsedNumbersMask == usedNumbersMask ? initUsedNumbersMask : nextUsedNumbersMask;
    }

    int tryCreateSubset(std::vector<int> const &numbers, int portionSum, int usedNumbersMask, size_t start) const
    {
        for (size_t index = start; index < numbers.size(); ++index)
        {
            const int maskValue = 1 << index;
            if ((usedNumbersMask & maskValue) == 0)
                continue;
            if (numbers[index] > portionSum)
                continue;
            usedNumbersMask &= ~maskValue;
            portionSum -= numbers[index];
            if (portionSum == 0)
                return usedNumbersMask;
            const int nextUsedNumbersMask = tryCreateSubset(numbers, portionSum, usedNumbersMask, index + 1);
            if (nextUsedNumbersMask != usedNumbersMask)
                return nextUsedNumbersMask;
            portionSum += numbers[index];
            usedNumbersMask |= maskValue;
        }
        return usedNumbersMask;
    }
};

}

namespace PartitionToKEqualSumSubsetsTask
{

TEST(PartitionToKEqualSumSubsetsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canPartitionKSubsets({4, 3, 2, 3, 5, 2, 1}, 4));
    ASSERT_EQ(false, solution.canPartitionKSubsets({1, 2, 3, 4}, 3));
}

}