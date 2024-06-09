#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string longestPrefix(std::string const &s) const
    {
        // p, m - for computing hash
        constexpr long long p = 31;
        constexpr long long m = 1000000009;
        constexpr long long alphabetStart = 'a';
        long long prefixHash = 0;
        long long pPower = 1;
        long long suffixHash = 0;
        std::vector<size_t> possibleSuffixes;
        possibleSuffixes.reserve(s.size());
        for (size_t index = 0; index < s.size() - 1; ++index)
        {
            const size_t rIndex = s.size() - 1 - index;
            prefixHash = (prefixHash + pPower * (s[index] - alphabetStart + 1)) % m;
            pPower = (pPower * p) % m;
            suffixHash = ((s[rIndex] - alphabetStart + 1) + p * suffixHash) % m;
            if (prefixHash == suffixHash)
                possibleSuffixes.emplace_back(rIndex);
        }
        for (size_t rIndex = 0; rIndex < possibleSuffixes.size(); ++rIndex)
        {
            const size_t index = possibleSuffixes.size() - 1 - rIndex;
            if (equals(s, possibleSuffixes[index]))
                return s.substr(possibleSuffixes[index]);
        }
        return "";
    }

private:
    [[nodiscard]] bool equals(std::string const &s, size_t suffixStart) const
    {
        for (size_t prefix = 0, suffix = suffixStart; suffix < s.size(); ++prefix, ++suffix)
        {
            if (s[prefix] != s[suffix])
                return false;
        }
        return true;
    }
};

}

namespace LongestHappyPrefixTask
{

TEST(LongestHappyPrefixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("l", solution.longestPrefix("level"));
    ASSERT_EQ("abab", solution.longestPrefix("ababab"));
}

TEST(LongestHappyPrefixTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ("", solution.longestPrefix("l"));
    ASSERT_EQ("", solution.longestPrefix("abc"));
    ASSERT_EQ(std::string(1999, 'a'), solution.longestPrefix(std::string(2000, 'a')));
}

}