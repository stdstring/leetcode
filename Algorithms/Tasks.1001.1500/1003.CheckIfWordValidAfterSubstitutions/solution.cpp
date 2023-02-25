#include <stack>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isValid(std::string const &s) const
    {
        std::stack<char> wordStack;
        for (char ch : s)
        {
            if (ch == 'a')
                wordStack.push(ch);
            else
            {
                if (wordStack.empty())
                    return false;
                ++wordStack.top();
                if (wordStack.top() != ch)
                    return false;
                if (wordStack.top() == 'c')
                    wordStack.pop();
            }
        }
        return wordStack.empty();
    }
};

}

namespace CheckIfWordValidAfterSubstitutionsTask
{

TEST(CheckIfWordValidAfterSubstitutionsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isValid("aabcbc"));
    ASSERT_EQ(true, solution.isValid("abcabcababcc"));
    ASSERT_EQ(false, solution.isValid("abccba"));
    ASSERT_EQ(false, solution.isValid("cababc"));
}

TEST(CheckIfWordValidAfterSubstitutionsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isValid("aabbcc"));
}

}