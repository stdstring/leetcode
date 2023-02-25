#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int expressiveWords(std::string const &s, std::vector<std::string> const &words) const
    {
        return static_cast<int>(std::count_if(words.cbegin(), words.cend(), [&s, this](std::string const &word){ return isExpressiveWord(s, word); }));
    }

private:
    size_t calcLetterGroupSize(std::string const &source, size_t index, char letter) const
    {
        size_t letterGroupSize = 0;
        while ((index < source.size()) && (source[index] == letter))
        {
            ++index;
            ++letterGroupSize;
        }
        return letterGroupSize;
    }

    bool isExpressiveWord(std::string const &source, std::string const &word) const
    {
        constexpr size_t letterGroupDelta = 3;
        size_t sourceIndex = 0;
        size_t wordIndex = 0;
        while ((sourceIndex < source.size()) && (wordIndex < word.size()))
        {
            const char letter = word[wordIndex];
            const size_t sourceLetterGroupSize = calcLetterGroupSize(source, sourceIndex, letter);
            const size_t wordLetterGroupSize = calcLetterGroupSize(word, wordIndex, letter);
            if (sourceLetterGroupSize < wordLetterGroupSize)
                return false;
            if ((sourceLetterGroupSize != wordLetterGroupSize) && (sourceLetterGroupSize < letterGroupDelta))
                return false;
            sourceIndex += sourceLetterGroupSize;
            wordIndex += wordLetterGroupSize;
        }
        return (sourceIndex == source.size()) && (wordIndex == word.size());
    }
};

}

namespace ExpressiveWordsTask
{

TEST(ExpressiveWordsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.expressiveWords("heeellooo", {"hello", "hi", "helo"}));
}

TEST(ExpressiveWordsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(3, solution.expressiveWords("dddiiiinnssssssoooo", {"dinnssoo", "ddinso", "ddiinnso", "ddiinnssoo", "ddiinso", "dinsoo", "ddiinsso", "dinssoo", "dinso"}));
}

}