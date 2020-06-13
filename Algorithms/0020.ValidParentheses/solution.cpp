#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isValid(std::string const &s)
    {
        const std::unordered_set<char> openBrackets = {'(', '[', '{'};
        std::unordered_map<char, char> closeBracketMap = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
        std::stack<char> brackets;
        for(char ch : s)
        {
            if (openBrackets.count(ch) > 0)
            {
                brackets.push(ch);
            }
            else
            {
                if (brackets.empty())
                    return false;
                char openBracket = brackets.top();
                brackets.pop();
                if (ch != closeBracketMap[openBracket])
                    return false;
            }
        }
        return brackets.empty();
    }
};

}

namespace ValidParenthesesTask
{

TEST(ValidParenthesesTask, Examples)
{
    Solution solution;
    ASSERT_EQ(true, solution.isValid("()"));
    ASSERT_EQ(true, solution.isValid("()[]{}"));
    ASSERT_EQ(false, solution.isValid("(]"));
    ASSERT_EQ(false, solution.isValid("([)]"));
    ASSERT_EQ(true, solution.isValid("{[]}"));
}

}