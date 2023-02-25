#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numSplits(std::string const &s) const
    {
        std::array<size_t, AlphabetSize> leftLetterData{};
        leftLetterData.fill(0);
        size_t leftDistinctLetters = 0;
        std::array<size_t, AlphabetSize> rightLetterData(generateLetterData(s));
        size_t rightDistinctLetters = calcDistinctLetters(rightLetterData);
        size_t goodSplitCount = 0;
        for (char ch : s)
        {
            if (leftLetterData[ch - FirstLetter] == 0)
                ++leftDistinctLetters;
            ++leftLetterData[ch - FirstLetter];
            --rightLetterData[ch - FirstLetter];
            if (rightLetterData[ch - FirstLetter] == 0)
                --rightDistinctLetters;
            if (leftDistinctLetters > rightDistinctLetters)
                return static_cast<int>(goodSplitCount);
            if (leftDistinctLetters == rightDistinctLetters)
                ++goodSplitCount;
        }
        return static_cast<int>(goodSplitCount);
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t FirstLetter = 'a';

    std::array<size_t, AlphabetSize> generateLetterData(std::string const &source) const
    {
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        for (char ch : source)
            ++letterData[ch - FirstLetter];
        return letterData;
    }

    size_t calcDistinctLetters(std::array<size_t, AlphabetSize> const &letterData) const
    {
        size_t distinctLetters = 0;
        for (size_t value : letterData)
        {
            if (value > 0)
                ++distinctLetters;
        }
        return distinctLetters;
    }
};

}

namespace NumberOfGoodWaysToSplitStringTask
{

TEST(NumberOfGoodWaysToSplitStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.numSplits("aacaba"));
    ASSERT_EQ(1, solution.numSplits("abcd"));
    ASSERT_EQ(4, solution.numSplits("aaaaa"));
    ASSERT_EQ(2, solution.numSplits("acbadbaada"));
}

}