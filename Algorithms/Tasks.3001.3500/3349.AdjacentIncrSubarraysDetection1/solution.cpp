#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool hasIncreasingSubarrays(std::vector<int> const &nums, int k) const
    {
        size_t expectedSize = k;
        for (size_t start = 0; start <= nums.size() - 2 * expectedSize;)
        {
            const size_t currentSize = getMaxIncreasingSubarraysSize(nums, start, expectedSize);
            if (currentSize == expectedSize)
                return true;
            start += currentSize;
        }
        return false;
    }

private:
    [[nodiscard]] size_t getMaxIncreasingSubarraysSize(std::vector<int> const &nums, size_t start, size_t maxSize) const
    {
        size_t currentSize = 1;
        for (size_t current = start + 1; currentSize < maxSize; ++current)
        {
            if ((nums[current - 1] >= nums[current]) || (nums[current + maxSize - 1] >= nums[current  + maxSize]))
                break;
            ++currentSize;
        }
        return currentSize;
    }
};

}

namespace AdjacentIncrSubarraysDetection1Task
{

TEST(AdjacentIncrSubarraysDetection1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.hasIncreasingSubarrays({2, 5, 7, 8, 9, 2, 3, 4, 3, 1}, 3));
    ASSERT_EQ(false, solution.hasIncreasingSubarrays({1, 2, 3, 4, 4, 4, 4, 5, 6, 7}, 5));
}

}