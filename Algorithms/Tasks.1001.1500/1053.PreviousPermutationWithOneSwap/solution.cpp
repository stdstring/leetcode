#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> prevPermOpt1(std::vector<int> const &arr) const
    {
        std::vector<int> result(arr);
        std::stack<size_t> decreasingItemStack;
        size_t rIndex = 0;
        for (;rIndex < result.size(); ++rIndex)
        {
            const size_t index = result.size() - 1 - rIndex;
            if (!decreasingItemStack.empty() && (result[index] > result[decreasingItemStack.top()]))
                break;
            if (!decreasingItemStack.empty() && (result[index] == result[decreasingItemStack.top()]))
                decreasingItemStack.pop();
            decreasingItemStack.push(index);
        }
        if (rIndex == result.size())
            return result;
        const size_t fromIndex = result.size() - 1 - rIndex;
        size_t toIndex = fromIndex;
        while (!decreasingItemStack.empty() && (result[fromIndex] > result[decreasingItemStack.top()]))
        {
            toIndex = decreasingItemStack.top();
            decreasingItemStack.pop();
        }
        std::swap(result[fromIndex], result[toIndex]);
        return result;
    }
};

}

namespace PreviousPermutationWithOneSwapTask
{

TEST(PreviousPermutationWithOneSwapTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 1, 2}), solution.prevPermOpt1({3, 2, 1}));
    ASSERT_EQ(std::vector<int>({1, 1, 5}), solution.prevPermOpt1({1, 1, 5}));
    ASSERT_EQ(std::vector<int>({1, 7, 4, 6, 9}), solution.prevPermOpt1({1, 9, 4, 6, 7}));
}

TEST(PreviousPermutationWithOneSwapTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 1, 3}), solution.prevPermOpt1({3, 1, 1, 3}));
}

}