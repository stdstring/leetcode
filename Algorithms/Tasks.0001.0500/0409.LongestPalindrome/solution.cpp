#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int longestPalindrome(std::string const &s) const
    {
        std::array<size_t, 2 * alphabetSize> usedLetters{};
        usedLetters.fill(0);
        for (char ch : s)
            ++usedLetters[isupper(ch) ? ch - 'A' : alphabetSize + ch - 'a'];
        size_t pairsCount = 0;
        bool hasUnpaired = false;
        for (size_t usedLetter : usedLetters)
        {
            if (usedLetter > 0)
            {
                pairsCount += (usedLetter / 2);
                hasUnpaired |= (usedLetter % 2 == 1);
            }
        }
        return static_cast<int>(2 * pairsCount + (hasUnpaired ? 1 : 0));
    }

private:
    static constexpr size_t alphabetSize = 26;
};

}

namespace LongestPalindromeTask
{

TEST(LongestPalindromeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(7, solution.longestPalindrome("abccccdd"));
    ASSERT_EQ(1, solution.longestPalindrome("a"));
    ASSERT_EQ(2, solution.longestPalindrome("bb"));
}

}