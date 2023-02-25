#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool canJump(std::vector<int> const &nums) const
    {
        size_t currentIndex = 0;
        size_t maxIndex = nums.front();
        while (maxIndex < (nums.size() - 1))
        {
            if (maxIndex == currentIndex)
                return false;
            size_t nextMaxIndex = maxIndex;
            for (size_t index = currentIndex; index <= maxIndex; ++index)
                nextMaxIndex = std::max(nextMaxIndex, index + nums[index]);
            currentIndex = maxIndex;
            maxIndex = nextMaxIndex;
        }
        return true;
    }
};

}

namespace JumpGameTask
{

TEST(JumpGameTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canJump({2, 3, 1, 1, 4}));
    ASSERT_EQ(false, solution.canJump({3, 2, 1, 0, 4}));
}

}