#include <string>
#include <unordered_map>
#include <unordered_set>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countPalindromicSubsequence(std::string const &s) const
    {
        constexpr int alphabetSize = 26;
        constexpr int alphabetStart = 'a';
        std::unordered_set<char> oneLetterPrefixes;
        std::unordered_map<char, int> twoLetterPrefixes;
        std::unordered_map<char, int> palindromicSubsequences;
        size_t result = 0;
        for (const char ch : s)
        {
            const int secondChars = twoLetterPrefixes[ch];
            for (int secondChar = 0; secondChar < alphabetSize; ++secondChar)
            {
                const int secondCharBit = 1 << secondChar;
                if (((secondChars & secondCharBit) != 0) && ((palindromicSubsequences[ch] & secondCharBit) == 0))
                {
                    palindromicSubsequences[ch] |= secondCharBit;
                    ++result;
                }
            }
            for (char prefix : oneLetterPrefixes)
                twoLetterPrefixes[prefix] |= (1 << (ch - alphabetStart));
            oneLetterPrefixes.emplace(ch);
        }
        return static_cast<int>(result);
    }
};

}

namespace UniqueLength3PalindromicSubseqTask
{

TEST(UniqueLength3PalindromicSubseqTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countPalindromicSubsequence("aabca"));
    ASSERT_EQ(0, solution.countPalindromicSubsequence("adc"));
    ASSERT_EQ(4, solution.countPalindromicSubsequence("bbcbaba"));
}

}