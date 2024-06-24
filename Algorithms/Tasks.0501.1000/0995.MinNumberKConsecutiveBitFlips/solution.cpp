#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minKBitFlips(std::vector<int> const &nums, int k) const
    {
        const size_t subarraySize = k;
        int flipCount = 0;
        int currentFlipResult = 0;
        std::queue<size_t> flipEndQueue;
        for (size_t index = 0; index <= nums.size() - subarraySize; ++index)
        {
            const int currentBit = (nums[index] + currentFlipResult) % 2;
            if (currentBit == 0)
            {
                flipEndQueue.emplace(index + subarraySize - 1);
                ++currentFlipResult;
                ++flipCount;
            }
            if (!flipEndQueue.empty() && (flipEndQueue.front() == index))
            {
                flipEndQueue.pop();
                --currentFlipResult;
            }
        }
        for (size_t index = nums.size() - subarraySize + 1; index < nums.size(); ++index)
        {
            const int currentBit = (nums[index] + currentFlipResult) % 2;
            if (currentBit == 0)
                return -1;
            if (!flipEndQueue.empty() && (flipEndQueue.front() == index))
            {
                flipEndQueue.pop();
                --currentFlipResult;
            }
        }
        return flipCount;
    }
};

}

namespace MinNumberKConsecutiveBitFlipsTask
{

TEST(MinNumberKConsecutiveBitFlipsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minKBitFlips({0, 1, 0}, 1));
    ASSERT_EQ(-1, solution.minKBitFlips({1, 1, 0}, 2));
    ASSERT_EQ(3, solution.minKBitFlips({0, 0, 0, 1, 0, 1, 1, 0}, 3));
}

}