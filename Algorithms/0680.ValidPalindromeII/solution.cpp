#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool validPalindrome(std::string const &s) const
    {
        bool hasDelete = false;
        size_t start = 0;
        size_t finish = s.size() - 1;
        while (start < finish)
        {
            if (s[start] == s[finish])
            {
                ++start;
                --finish;
            }
            else
            {
                if (hasDelete)
                    return false;
                hasDelete = true;
                if ((start + 1) == finish)
                    return true;
                // process "...abc...cbab..."
                if ((s[start + 1] == s[finish]) && (s[start] == s[finish - 1]) && (s[start + 2] == s[finish - 1]))
                    ++start;
                // process "...babc...cba..."
                else if ((s[start + 1] == s[finish]) && (s[start] == s[finish - 1]) && (s[start + 1] == s[finish - 2]))
                    --finish;
                // process "...xab...ba..."
                else if (s[start + 1] == s[finish])
                    ++start;
                // process "...ab...bax..."
                else if (s[start] == s[finish - 1])
                    --finish;
                else
                    return false;
            }
        }
        return true;
    }
};

}

namespace ValidPalindromeIITask
{

TEST(ValidPalindromeIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.validPalindrome("aba"));
    ASSERT_EQ(true, solution.validPalindrome("abca"));
}

TEST(ValidPalindromeIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.validPalindrome("aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga"));
}

}