#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct PalindromeData
{
    PalindromeData(size_t start, size_t length) : Start(start), Length(length)
    {
    }

    size_t Start;
    size_t Length;
};

class Solution
{
public:
    std::string longestPalindrome(std::string const &s) const
    {
        std::vector<PalindromeData> current;
        // init phase
        for (size_t index = 0; index < s.size();)
        {
            PalindromeData data(index, 0);
            while ((index < s.size()) && (s[index] == s[data.Start]))
                ++index;
            data.Length = index - data.Start;
            current.push_back(data);
        }
        // process
        size_t bestStart = 0;
        size_t bestLength = 0;
        while (!current.empty())
        {
            std::vector<PalindromeData> next;
            for (PalindromeData const &data : current)
            {
                if ((data.Start == 0) ||
                    ((data.Start + data.Length) == s.size()) ||
                    (s[data.Start - 1] != s[data.Start + data.Length]))
                    calcBestPalindrome(bestStart, bestLength, data);
                else
                    next.emplace_back(data.Start - 1, data.Length + 2);
            }
            std::swap(current, next);
        }
        return s.substr(bestStart, bestLength);
    }

private:
    void calcBestPalindrome(size_t &bestStart, size_t &bestLength, PalindromeData const &data) const
    {
        if (data.Length > bestLength)
        {
            bestStart = data.Start;
            bestLength = data.Length;
        }
    }
};

}

namespace LongestPalindromicSubstringTask
{

TEST(LongestPalindromicSubstringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("bab", solution.longestPalindrome("babad"));
    ASSERT_EQ("bb", solution.longestPalindrome("cbbd"));
    ASSERT_EQ("a", solution.longestPalindrome("a"));
    ASSERT_EQ("a", solution.longestPalindrome("ac"));
}

}