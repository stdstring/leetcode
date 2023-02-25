#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string removeOuterParentheses(std::string const &s) const
    {
        std::string result;
        size_t balance = 0;
        for (const char ch : s)
        {
            switch (ch)
            {
                case '(':
                    if (balance > 0)
                        result.push_back(ch);
                    ++balance;
                    break;
                case ')':
                    --balance;
                    if (balance > 0)
                        result.push_back(ch);
                    break;
                default:
                    break;
            }
        }
        return result;
    }
};

}

namespace RemoveOutermostParenthesesTask
{

TEST(RemoveOutermostParenthesesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("()()()", solution.removeOuterParentheses("(()())(())"));
    ASSERT_EQ("()()()()(())", solution.removeOuterParentheses("(()())(())(()(()))"));
    ASSERT_EQ("", solution.removeOuterParentheses("()()"));
}

}