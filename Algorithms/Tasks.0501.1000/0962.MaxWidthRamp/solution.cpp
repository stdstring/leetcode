#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxWidthRamp(std::vector<int> const &nums) const
    {
        std::stack<size_t> decreaseStack;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (decreaseStack.empty() || (nums[decreaseStack.top()] > nums[index]))
                decreaseStack.push(index);
        }
        size_t maxWidth = 0;
        for (size_t rIndex = 0; rIndex < nums.size(); ++rIndex)
        {
            size_t index = nums.size() - 1 - rIndex;
            while (!decreaseStack.empty() && (nums[decreaseStack.top()] <= nums[index]))
            {
                maxWidth = std::max(maxWidth, index - decreaseStack.top());
                decreaseStack.pop();
            }
        }
        return static_cast<int>(maxWidth);
    }
};

}

namespace MaxWidthRampTask
{

TEST(MaxWidthRampTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxWidthRamp({6, 0, 8, 2, 1, 5}));
    ASSERT_EQ(7, solution.maxWidthRamp({9, 8, 1, 0, 1, 9, 4, 0, 4, 1}));
}

}