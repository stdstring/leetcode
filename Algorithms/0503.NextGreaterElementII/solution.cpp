#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> nextGreaterElements(std::vector<int> const &nums) const
    {
        if (nums.empty())
            return {};
        std::vector<int> result(nums.size(), -1);
        const int maxValue = *std::max_element(nums.cbegin(), nums.cend());
        std::stack<size_t> indicesStack;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            while (!indicesStack.empty() && (nums[indicesStack.top()] < nums[index]))
            {
                result[indicesStack.top()] = nums[index];
                indicesStack.pop();
            }
            if (nums[index] < maxValue)
                indicesStack.push(index);
        }
        size_t index = 0;
        while (!indicesStack.empty())
        {
            if (nums[indicesStack.top()] < nums[index])
            {
                result[indicesStack.top()] = nums[index];
                indicesStack.pop();
            }
            else
                ++index;
        }
        return result;
    }
};

}

namespace NextGreaterElementIITask
{

TEST(NextGreaterElementIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, -1, 2}), solution.nextGreaterElements({1, 2, 1}));
}

TEST(NextGreaterElementIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>(), solution.nextGreaterElements({}));
}

}