#include <string>
#include <stdexcept>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkValidString(std::string const &s) const
    {
        int balance = 0;
        int asteriskCount = 0;
        for (const char ch : s)
        {
            if (!processChar(ch, '(', ')', balance, asteriskCount))
                return false;
        }
        if (balance > asteriskCount)
            return false;
        balance = 0;
        asteriskCount = 0;
        for (auto iterator = s.crbegin(); iterator != s.crend(); ++iterator)
        {
            if (!processChar(*iterator, ')', '(', balance, asteriskCount))
                return false;
        }
        return balance <= asteriskCount;
    }

private:
    [[nodiscard]] bool processChar(char ch, char leftBrace, char rightBrace, int &balance, int &asteriskCount) const
    {
        if (ch == leftBrace)
        {
            ++balance;
            return true;
        }
        if (ch == rightBrace)
        {
            if ((balance == 0) && (asteriskCount == 0))
                return false;
            --(balance > 0 ? balance : asteriskCount);
            return true;
        }
        if (ch == '*')
        {
            ++asteriskCount;
            return true;
        }
        throw std::logic_error("Unexpected char");
    }
};

}

namespace ValidParenthesisStringTask
{

TEST(ValidParenthesisStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkValidString("()"));
    ASSERT_EQ(true, solution.checkValidString("(*)"));
    ASSERT_EQ(true, solution.checkValidString("(*))"));
}

TEST(ValidParenthesisStringTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.checkValidString("(((((*(()((((*((**(((()()*)()()()*((((**)())*)*)))))))(())(()))())((*()()(((()((()*(())*(()**)()(())"));
}

}