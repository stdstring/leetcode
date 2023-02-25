#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int scoreOfParentheses(std::string const &s) const
    {
        size_t index = 0;
        return calcValue(s, index);
    }

private:
    int calcValue(std::string const &source, size_t &index) const
    {
        int value = 0;
        while ((index < source.size()) && (source[index] == '('))
        {
            index += 1;
            if (source[index] == ')')
                value += 1;
            else
                value += (2 * calcValue(source, index));
            index += 1;
        }
        return value;
    }
};

}

namespace ScoreOfParenthesesTask
{

TEST(ScoreOfParenthesesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.scoreOfParentheses("()"));
    ASSERT_EQ(2, solution.scoreOfParentheses("(())"));
    ASSERT_EQ(2, solution.scoreOfParentheses("()()"));
    ASSERT_EQ(6, solution.scoreOfParentheses("(()(()))"));
}

}