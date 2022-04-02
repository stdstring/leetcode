#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool validPalindrome(std::string const &s) const
    {
        return validPalindrome(s, 0, s.size() - 1, true);
    }

private:
    [[nodiscard]] bool validPalindrome(std::string const &s, size_t start, size_t finish, bool allowDelete) const
    {
        while (start < finish)
        {
            if (s[start] == s[finish])
            {
                ++start;
                --finish;
            }
            else
            {
                if (!allowDelete)
                    return false;
                if ((start + 1) == finish)
                    return true;
                bool result = false;
                if (s[start + 1] == s[finish])
                    result |= validPalindrome(s, start + 1, finish, false);
                if (s[start] == s[finish - 1])
                    result |= validPalindrome(s, start, finish - 1, false);
                return result;
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
    ASSERT_EQ(true, solution.validPalindrome("acxcybycxcxa"));
    ASSERT_EQ(true, solution.validPalindrome("aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga"));
}

}