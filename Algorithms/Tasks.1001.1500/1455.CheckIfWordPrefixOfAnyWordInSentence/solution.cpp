#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int isPrefixOfWord(std::string const &sentence, std::string const &searchWord) const
    {
        int wordIndex = 1;
        for (size_t sentenceIndex = 0, wordCharIndex = 0; sentenceIndex < sentence.size(); ++sentenceIndex)
        {
            if (sentence[sentenceIndex] == ' ')
            {
                ++wordIndex;
                wordCharIndex = 0;
                continue;
            }
            if (wordCharIndex != std::string::npos)
                wordCharIndex = (sentence[sentenceIndex] == searchWord[wordCharIndex]) ? (wordCharIndex + 1) : std::string::npos;
            if (wordCharIndex == searchWord.size())
                return wordIndex;
        }
        return -1;
    }
};

}

namespace CheckIfWordPrefixOfAnyWordInSentenceTask
{

TEST(CheckIfWordPrefixOfAnyWordInSentenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.isPrefixOfWord("i love eating burger", "burg"));
    ASSERT_EQ(2, solution.isPrefixOfWord("this problem is an easy problem", "pro"));
    ASSERT_EQ(-1, solution.isPrefixOfWord("i am tired", "you"));
}

}