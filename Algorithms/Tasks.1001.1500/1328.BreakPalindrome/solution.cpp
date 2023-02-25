#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string breakPalindrome(std::string const &palindrome) const
    {
        if (palindrome.size() == 1)
            return "";
        std::string result(palindrome);
        bool changed = false;
        for (size_t index = 0; index < palindrome.size() / 2; ++index)
        {
            if (palindrome[index] != 'a')
            {
                result[index] = 'a';
                changed = true;
                break;
            }
        }
        if (!changed)
            result.back() = 'b';
        return result;
    }
};

}

namespace BreakPalindromeTask
{

TEST(BreakPalindromeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("aaccba", solution.breakPalindrome("abccba"));
    ASSERT_EQ("", solution.breakPalindrome("a"));
    ASSERT_EQ("ab", solution.breakPalindrome("aa"));
    ASSERT_EQ("abb", solution.breakPalindrome("aba"));
}

}