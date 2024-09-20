#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string shortestPalindrome(std::string const &s) const
    {
        std::string reversed(s);
        std::ranges::reverse(reversed);
        std::string pattern = s + "@" + reversed;
        // KMP (Knuth–Morris–Pratt)
        std::vector<size_t> lps(pattern.size(), 0);
        size_t length = 0;
        for (size_t index = 1; index < pattern.size(); ++index)
        {
            while ((pattern[index] != pattern[length]) && (length > 0))
                length = lps[length - 1];
            if (pattern[index] == pattern[length])
                ++length;
            lps[index] = length;
        }
        size_t commonLength = lps.back();
        return reversed.substr(0, reversed.size() - commonLength) + s;
    }
};

}

namespace ShortestPalindromeTask
{

TEST(ShortestPalindromeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("aaacecaaa", solution.shortestPalindrome("aacecaaa"));
    ASSERT_EQ("dcbabcd", solution.shortestPalindrome("abcd"));
}

TEST(ShortestPalindromeTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("ababbabbbababbbabbaba", solution.shortestPalindrome("ababbbabbaba"));
}

}