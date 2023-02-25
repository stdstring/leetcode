#include <algorithm>
#include <stack>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string minRemoveToMakeValid(std::string const &s) const
    {
        std::vector<size_t> removedPositions;
        size_t parenthesesBalance = 0;
        std::stack<size_t> openParenthesesPositions;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] == '(')
            {
                ++parenthesesBalance;
                openParenthesesPositions.push(index);
            }
            if (s[index] == ')')
            {
                if (parenthesesBalance == 0)
                    removedPositions.push_back(index);
                else
                {
                    --parenthesesBalance;
                    openParenthesesPositions.pop();
                }
            }
        }
        while (!openParenthesesPositions.empty())
        {
            removedPositions.push_back(openParenthesesPositions.top());
            openParenthesesPositions.pop();
        }
        std::sort(removedPositions.begin(), removedPositions.end());
        auto iterator = removedPositions.cbegin();
        std::string result;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if ((s[index] == '(' || s[index] == ')') && iterator != removedPositions.cend() && *iterator == index)
                ++iterator;
            else
                result.push_back(s[index]);
        }
        return result;
    }
};

}

namespace MinRemoveToMakeValidParenthesesTask
{

TEST(MinRemoveToMakeValidParenthesesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("lee(t(c)o)de", solution.minRemoveToMakeValid("lee(t(c)o)de)"));
    ASSERT_EQ("ab(c)d", solution.minRemoveToMakeValid("a)b(c)d"));
    ASSERT_EQ("", solution.minRemoveToMakeValid("))(("));
    ASSERT_EQ("a(b(c)d)", solution.minRemoveToMakeValid("(a(b(c)d)"));
}

}