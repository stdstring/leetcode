#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isPalindrome(std::string const &s) const
    {
        if (s.empty())
            return true;
        size_t front = 0;
        size_t back = s.size() - 1;
        while (front < back)
        {
            if (!isalnum(s[front]))
            {
                ++front;
                continue;
            }
            if (!isalnum(s[back]))
            {
                --back;
                continue;
            }
            if (!compareChars(s[front], s[back]))
                return false;
            ++front;
            --back;
        }
        return true;
    }

private:
    bool compareChars(char ch1, char ch2) const
    {
        if (ch1 == ch2)
            return true;
        if (isupper(ch1) || isupper(ch2))
            return tolower(ch1) == tolower(ch2);
        return false;
    }
};

}

namespace ValidPalindromeTask
{

TEST(ValidPalindromeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isPalindrome("A man, a plan, a canal: Panama"));
    ASSERT_EQ(false, solution.isPalindrome("race a car"));
}

TEST(ValidPalindromeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isPalindrome(""));
}

}