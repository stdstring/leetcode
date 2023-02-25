#include <array>
#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isItPossible(std::string const& word1, std::string const& word2) const
    {
        auto const& [letterData1, differentLetters1] = generateLetterData(word1);
        auto const& [letterData2, differentLetters2] = generateLetterData(word2);
        return differentLetters1 < differentLetters2 ?
               checkWords(letterData1, differentLetters1, letterData2, differentLetters2) :
               checkWords(letterData2, differentLetters2, letterData1, differentLetters1);
    }

private:
    static constexpr size_t AlphabetStart = 'a';
    static constexpr size_t AlphabetSize = 26;

    [[nodiscard]] std::pair<std::array<size_t, AlphabetSize>, size_t> generateLetterData(std::string const &word) const
    {
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        size_t differentLetters = 0;
        for (const char ch : word)
        {
            const size_t index = ch - AlphabetStart;
            if (letterData[index] == 0)
                ++differentLetters;
            ++letterData[index];
        }
        return {letterData, differentLetters};
    }

    [[nodiscard]] bool checkWords(std::array<size_t, AlphabetSize> const &letterData1,
                                  size_t differentLetters1,
                                  std::array<size_t, AlphabetSize> const &letterData2,
                                  size_t differentLetters2) const
    {
        // require differentLetters1 <= differentLetters2
        if ((differentLetters2 - differentLetters1) > 2)
            return false;
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            switch (differentLetters2 - differentLetters1)
            {
                case 0:
                    if ((letterData1[index] > 0) && (letterData2[index] > 0))
                        return true;
                    if ((letterData1[index] > 1) && (letterData2[index] == 0) && hasIncrease1Move(letterData1, letterData2, index))
                        return true;
                    if ((letterData1[index] == 1) && (letterData2[index] > 0) && hasDecrease2Move(letterData1, letterData2, index))
                        return true;
                    if ((letterData1[index] == 1) && (letterData2[index] == 0) && hasIncrease1Decrease2Move(letterData1, letterData2, index))
                        return true;
                    break;
                case 1:
                    if ((letterData1[index] > 1) && (letterData2[index] > 0) && hasDecrease2Move(letterData1, letterData2, index))
                        return true;
                    if ((letterData1[index] > 1) && (letterData2[index] > 0) && hasIncrease1Move(letterData1, letterData2, index))
                        return true;
                    if ((letterData1[index] == 1) && (letterData2[index] > 0) && hasIncrease1Decrease2Move(letterData1, letterData2, index))
                        return true;
                    break;
                case 2:
                    if ((letterData1[index] > 1) && (letterData2[index] > 0) && hasIncrease1Decrease2Move(letterData1, letterData2, index))
                        return true;
                    break;
                default:
                    throw std::logic_error("Unexpected difference differentLetters2 - differentLetters1");
            }
        }
        return false;
    }

    [[nodiscard]] bool hasIncrease1Move(std::array<size_t, AlphabetSize> const &letterData1,
                                        std::array<size_t, AlphabetSize> const &letterData2,
                                        size_t move1) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if (index == move1)
                continue;
            if ((letterData1[index] == 0) && (letterData2[index] > 1))
                return true;
        }
        return false;
    }

    [[nodiscard]] bool hasDecrease2Move(std::array<size_t, AlphabetSize> const &letterData1,
                                        std::array<size_t, AlphabetSize> const &letterData2,
                                        size_t move1) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if (index == move1)
                continue;
            if ((letterData1[index] > 0) && (letterData2[index] == 1))
                return true;
        }
        return false;
    }

    [[nodiscard]] bool hasIncrease1Decrease2Move(std::array<size_t, AlphabetSize> const &letterData1,
                                                 std::array<size_t, AlphabetSize> const &letterData2,
                                                 size_t move1) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if (index == move1)
                continue;
            if ((letterData1[index] == 0) && (letterData2[index] == 1))
                return true;
        }
        return false;
    }
};

}

namespace MakeNumberDistinctCharsEqualTask
{

TEST(MakeNumberDistinctCharsEqualTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.isItPossible("ac", "b"));
    ASSERT_EQ(true, solution.isItPossible("abcc", "aab"));
    ASSERT_EQ(true, solution.isItPossible("abcde", "fghij"));
}

TEST(MakeNumberDistinctCharsEqualTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.isItPossible("a", "bb"));
    ASSERT_EQ(false, solution.isItPossible("aa", "ab"));
}

}