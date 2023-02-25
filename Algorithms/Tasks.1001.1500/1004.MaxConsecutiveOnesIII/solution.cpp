#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestOnes(std::vector<int> const &nums, int k) const
    {
        const size_t maxSwapCount = k;
        size_t bestSize = 0;
        size_t start = 0;
        size_t swapCount = 0;
        size_t finish = 0;
        while (finish < nums.size())
        {
            if (nums[finish] == 1)
                ++finish;
            else if (swapCount < maxSwapCount)
            {
                ++swapCount;
                ++finish;
            }
            else
            {
                bestSize = std::max(bestSize, finish - start);
                while ((start < finish) && (nums[start] == 1))
                    ++start;
                ++start;
                ++finish;
            }
        }
        return static_cast<int>(std::max(bestSize, nums.size() - start));
    }
};

}

namespace MaxConsecutiveOnesIIITask
{

TEST(MaxConsecutiveOnesIIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.longestOnes({1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 2));
    ASSERT_EQ(10, solution.longestOnes({0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}, 3));
    ASSERT_EQ(4, solution.longestOnes({0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}, 0));
}

}