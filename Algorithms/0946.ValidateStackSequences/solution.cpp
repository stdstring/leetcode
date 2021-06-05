#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool validateStackSequences(std::vector<int> const &pushed, std::vector<int> const &popped) const
    {
        std::stack<int> stack;
        size_t pushedIndex = 0;
        size_t poppedIndex = 0;
        while ((pushedIndex < pushed.size()) && (poppedIndex < popped.size()))
        {
            push(stack, pushed, pushedIndex, popped[poppedIndex]);
            pop(stack, popped, poppedIndex);
        }
        return (pushedIndex == pushed.size()) && (poppedIndex == popped.size());
    }

private:
    void push(std::stack<int> &stack, std::vector<int> const &pushed, size_t &pushedIndex, int poppedCurrent) const
    {
        while ((pushedIndex < pushed.size()) && (stack.empty() || stack.top() != poppedCurrent))
            stack.push(pushed[pushedIndex++]);
    }

    void pop(std::stack<int> &stack, std::vector<int> const &popped, size_t &poppedIndex) const
    {
        while ((poppedIndex < popped.size()) && !stack.empty() && (stack.top() == popped[poppedIndex]))
        {
            stack.pop();
            ++poppedIndex;
        }
    }
};

}

namespace ValidateStackSequencesTask
{

TEST(ValidateStackSequencesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.validateStackSequences({1, 2, 3, 4, 5}, {4, 5, 3, 2, 1}));
    ASSERT_EQ(false, solution.validateStackSequences({1, 2, 3, 4, 5}, {4, 3, 5, 1, 2}));
}

}