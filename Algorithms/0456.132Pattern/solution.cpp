#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool find132pattern(std::vector<int> const &nums) const
    {
        if (nums.size() < 3)
            return false;
        std::vector<int> mins(nums.size(), 0);
        mins[0] = nums[0];
        for (size_t index = 1; index < nums.size(); ++index)
            mins[index] = std::min(nums[index], mins[index - 1]);
        std::stack<int> kStack;
        for (size_t index = nums.size() - 1; index > 0; --index)
        {
            if (nums[index] == mins[index])
                continue;
            while (!kStack.empty() && (kStack.top() <= mins[index]))
                kStack.pop();
            if (!kStack.empty() && (kStack.top() < nums[index]))
                return true;
            kStack.push(nums[index]);
        }
        return false;
    }
};

}

namespace OneThreeTwoPatternTask
{

TEST(OneThreeTwoPatternTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.find132pattern({1, 2, 3, 4}));
    ASSERT_EQ(true, solution.find132pattern({3, 1, 4, 2}));
    ASSERT_EQ(true, solution.find132pattern({-1, 3, 2, 0}));
}

}
