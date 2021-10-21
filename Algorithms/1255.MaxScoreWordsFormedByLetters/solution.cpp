#include <array>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxScoreWords(std::vector<std::string> const &words, std::vector<char> const &letters, std::vector<int> const &score) const
    {
        std::vector<std::array<size_t, AlphabetSize>> wordsLetterData;
        std::transform(words.cbegin(), words.cend(), std::back_inserter(wordsLetterData), [this](std::string const &word){ return createLetterData(word); });
        const std::array<size_t, AlphabetSize> sourceLettersData(createLetterData(letters));
        int bestScore = 0;
        for (size_t combination = 0; combination < (1LL << words.size()); ++combination)
        {
            std::array<size_t, AlphabetSize> usedLettersData{};
            usedLettersData.fill(0);
            for (size_t index = 0; index < words.size(); ++index)
            {
                if ((combination & (1LL << index)) != 0)
                    mergeLetterData(usedLettersData, wordsLetterData[index]);
            }
            if (canFormWord(sourceLettersData, usedLettersData))
                bestScore = std::max(bestScore, calcScore(usedLettersData, score));
        }
        return bestScore;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    template<typename TLetterSource> std::array<size_t, AlphabetSize> createLetterData(TLetterSource const &source) const
    {
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        for (const char ch : source)
            ++letterData[ch - AlphabetStart];
        return letterData;
    }

    void mergeLetterData(std::array<size_t, AlphabetSize> &dest, std::array<size_t, AlphabetSize> const &source) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
            dest[index] += source[index];
    }

    bool canFormWord(std::array<size_t, AlphabetSize> const &sourceLetters, std::array<size_t, AlphabetSize> const &wordsLetters) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if (sourceLetters[index] < wordsLetters[index])
                return false;
        }
        return true;
    }

    int calcScore(std::array<size_t, AlphabetSize> const &wordsLetters, std::vector<int> const &score) const
    {
        int result = 0;
        for (size_t index = 0; index < AlphabetSize; ++index)
            result += (wordsLetters[index] * score[index]);
        return result;
    }
};

}

namespace MaxScoreWordsFormedByLettersTask
{

TEST(MaxScoreWordsFormedByLettersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(23, solution.maxScoreWords({"dog", "cat", "dad", "good"},
                                         {'a', 'a', 'c', 'd', 'd', 'd', 'g', 'o', 'o'},
                                         {1, 0, 9, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    ASSERT_EQ(27, solution.maxScoreWords({"xxxz", "ax", "bx", "cx"},
                                         {'z', 'a', 'b', 'c', 'x', 'x', 'x'},
                                         {4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 10}));
    ASSERT_EQ(0, solution.maxScoreWords({"leetcode"},
                                        {'l', 'e', 't', 'c', 'o', 'd'},
                                        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}));
}

}