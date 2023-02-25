#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string minWindow(std::string const &s, std::string const &t) const
    {
        if (s.size() < t.size())
            return "";
        size_t minWindowStart = s.size();
        size_t minWindowSize = s.size();
        const std::array<size_t, LettersSize> targetLetterData(createLetterData(t, 0, t.size()));
        std::array<size_t, LettersSize> sourceLetterData(createLetterData(s, 0, t.size()));
        size_t start = 0;
        size_t finish = t.size() - 1;
        while ((finish - start + 1) >= t.size())
        {
            if (containsAllCharacters(sourceLetterData, targetLetterData))
            {
                const size_t currentWindowSize = finish - start + 1;
                if ((minWindowStart == s.size()) || (currentWindowSize < minWindowSize))
                {
                    minWindowSize = currentWindowSize;
                    minWindowStart = start;
                }
                --sourceLetterData[calcIndex(s[start++])];
            }
            else
            {
                if (finish == (s.size() - 1))
                    break;
                ++sourceLetterData[calcIndex(s[++finish])];
            }
        }
        return minWindowStart == s.size() ? "" : s.substr(minWindowStart, minWindowSize);
    }

private:
    constexpr static size_t AlphabetSize = 26;
    constexpr static size_t LettersSize = 2 * AlphabetSize;

    size_t calcIndex(char ch) const
    {
        constexpr size_t firstUpperLetter = 'A';
        constexpr size_t firstLowerLetter = 'a';
        const size_t index = ch - firstUpperLetter;
        return index < AlphabetSize ? index : ch - firstLowerLetter + AlphabetSize;
    }

    std::array<size_t, LettersSize> createLetterData(std::string const &source, size_t start, size_t size) const
    {
        std::array<size_t, LettersSize> letterData{};
        letterData.fill(0);
        for (size_t index = 0; index < size; ++index)
            ++letterData[calcIndex(source[start + index])];
        return letterData;
    }

    bool containsAllCharacters(std::array<size_t, LettersSize> const &sourceLetterData, std::array<size_t, LettersSize> const &targetLetterData) const
    {
        for (size_t index = 0; index < LettersSize; ++index)
        {
            if (sourceLetterData[index] < targetLetterData[index])
                return false;
        }
        return true;
    }
};

}

namespace MinimumWindowSubstringTask
{

TEST(MinimumWindowSubstringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("BANC", solution.minWindow("ADOBECODEBANC", "ABC"));
    ASSERT_EQ("a", solution.minWindow("a", "a"));
}

TEST(MinimumWindowSubstringTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("abc", solution.minWindow("abc", "ac"));
}

}