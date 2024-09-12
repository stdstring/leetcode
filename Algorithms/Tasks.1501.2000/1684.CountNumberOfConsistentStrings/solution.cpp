#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countConsistentStrings(std::string const &allowed, std::vector<std::string> const &words) const
    {
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<bool> allowedLetters(alphabetSize, false);
        for (const char ch : allowed)
            allowedLetters[ch - alphabetStart] = true;
        size_t result = 0;
        for (std::string const &word : words)
        {
            if (std::ranges::all_of(word, [&allowedLetters](char ch){ return allowedLetters[ch - alphabetStart]; }))
                ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace CountNumberOfConsistentStringsTask
{

TEST(CountNumberOfConsistentStringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countConsistentStrings("ab", {"ad", "bd", "aaab", "baa", "badab"}));
    ASSERT_EQ(7, solution.countConsistentStrings("abc", {"a", "b", "c", "ab", "ac", "bc", "abc"}));
    ASSERT_EQ(4, solution.countConsistentStrings("cad", {"cc", "acd", "b", "ba", "bac", "bad", "ac", "d"}));
}

}