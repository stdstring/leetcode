#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int jump(std::vector<int> const &nums) const
    {
        if (nums.size() == 1)
            return 0;
        size_t currentIndex = 0;
        size_t maxIndex = nums.front();
        int jumpCount = 1;
        while (maxIndex < (nums.size() - 1))
        {
            if (maxIndex == currentIndex)
                return -1;
            size_t nextMaxIndex = maxIndex;
            for (size_t index = currentIndex; index <= maxIndex; ++index)
                nextMaxIndex = std::max(nextMaxIndex, index + nums[index]);
            currentIndex = maxIndex;
            maxIndex = nextMaxIndex;
            ++jumpCount;
        }
        return jumpCount;
    }
};

}

namespace JumpGameIITask
{

TEST(JumpGameIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.jump({2, 3, 1, 1, 4}));
}

TEST(JumpGameIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.jump({0}));
}

}