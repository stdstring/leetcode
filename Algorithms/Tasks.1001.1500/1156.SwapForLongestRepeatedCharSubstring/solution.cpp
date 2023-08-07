#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxRepOpt1(std::string const &text) const
    {
        std::vector<size_t> textData(AlphabetSize, 0);
        for (const char ch : text)
            ++textData[ch - AlphabetStart];
        std::vector<size_t> windowData(AlphabetSize, 0);
        size_t windowStart = 0;
        size_t bestResult = 1;
        for (const char ch: text)
        {
            ++windowData[ch - AlphabetStart];
            while (!isSuitableWindows(windowData))
            {
                --windowData[text[windowStart] - AlphabetStart];
                ++windowStart;
            }
            auto [mainLetter, additionalLetter] = getUsedLetters(windowData);
            if (additionalLetter == AlphabetSize)
                bestResult = std::max(bestResult, windowData[mainLetter]);
            else
                bestResult = std::max(bestResult, windowData[mainLetter] + (windowData[mainLetter] < textData[mainLetter] ? 1: 0));
        }
        return static_cast<int>(bestResult);
    }

private:
    static constexpr size_t AlphabetStart = 'a';
    static constexpr size_t AlphabetSize = 26;

    [[nodiscard]] bool isSuitableWindows(std::vector<size_t> const &windowData) const
    {
        size_t differentLetterCount = 0;
        bool hasNonSingleLetter = false;
        for (const size_t letterCount : windowData)
        {
            if (letterCount == 0)
                continue;
            if (differentLetterCount == 2)
                return false;
            ++differentLetterCount;
            if ((letterCount > 1) && hasNonSingleLetter)
                return false;
            hasNonSingleLetter = letterCount > 1;
        }
        return true;
    }

    [[nodiscard]] std::pair<size_t, size_t> getUsedLetters(std::vector<size_t> const &windowData) const
    {
        size_t mainLetter = AlphabetSize;
        size_t additionalLetter = AlphabetSize;
        for (size_t letter = 0; letter < AlphabetSize; ++letter)
        {
            if (windowData[letter] > 1)
                mainLetter = letter;
            if (windowData[letter] == 1)
                (additionalLetter == AlphabetSize ? additionalLetter : mainLetter) = letter;
        }
        if (mainLetter == AlphabetSize)
            std::swap(mainLetter, additionalLetter);
        return {mainLetter, additionalLetter};
    }
};

}

namespace SwapForLongestRepeatedCharSubstringTask
{

TEST(SwapForLongestRepeatedCharSubstringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxRepOpt1("ababa"));
    ASSERT_EQ(6, solution.maxRepOpt1("aaabaaa"));
    ASSERT_EQ(5, solution.maxRepOpt1("aaaaa"));
}

}