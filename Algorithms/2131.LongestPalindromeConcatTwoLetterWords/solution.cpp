#include <array>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestPalindrome(std::vector<std::string> const &words) const
    {
        std::array<size_t, AlphabetSize * AlphabetSize> pairs{};
        pairs.fill(0);
        for (std::string const &word : words)
        {
            const size_t index = (word[0] - AlphabetStart) * AlphabetSize + (word[1] - AlphabetStart);
            ++pairs[index];
        }
        size_t palindromeWordsCount = 0;
        // choose center word
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            const size_t wordIndex = index * AlphabetSize + index;
            if ((pairs[wordIndex] % 2) == 1)
            {
                ++palindromeWordsCount;
                --pairs[wordIndex];
                break;
            }
        }
        // choose side pair
        for (size_t wordIndex = 0; wordIndex < AlphabetSize * AlphabetSize; ++wordIndex)
        {
            const size_t reverseWordIndex = generateReverseIndex(wordIndex);
            const size_t usedWordsCount = wordIndex == reverseWordIndex ? pairs[wordIndex] / 2 : std::min(pairs[wordIndex], pairs[reverseWordIndex]);
            pairs[wordIndex] -= usedWordsCount;
            pairs[reverseWordIndex] -= usedWordsCount;
            palindromeWordsCount += 2 * usedWordsCount;
        }
        return static_cast<int>(words.front().size() * palindromeWordsCount);
    }

private:
    static constexpr size_t AlphabetStart = 'a';
    static constexpr size_t AlphabetSize = 26;

    [[nodiscard]] size_t generateReverseIndex(size_t index) const
    {
        return (index % AlphabetSize) * AlphabetSize + (index / AlphabetSize);
    }
};

}

namespace LongestPalindromeConcatTwoLetterWordsTask
{

TEST(LongestPalindromeConcatTwoLetterWordsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.longestPalindrome({"lc", "cl", "gg"}));
    ASSERT_EQ(8, solution.longestPalindrome({"ab", "ty", "yt", "lc", "cl", "ab"}));
    ASSERT_EQ(2, solution.longestPalindrome({"cc", "ll", "xx"}));
}

TEST(LongestPalindromeConcatTwoLetterWordsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(22, solution.longestPalindrome({"dd", "aa", "bb", "dd", "aa", "dd", "bb", "dd", "aa", "cc", "bb", "cc", "dd", "cc"}));
}

}