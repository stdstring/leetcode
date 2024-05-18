#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string minimizeStringValue(std::string const &s) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::vector<size_t> usedLetters(alphabetSize, 0);
        size_t questionMarksCount = 0;
        for (const char ch : s)
        {
            if (ch == '?')
                ++questionMarksCount;
            else
                ++usedLetters[ch - alphabetStart];
        }
        std::string replaceData(questionMarksCount, ' ');
        for (size_t index = 0; index < questionMarksCount; ++index)
        {
            size_t minCount = usedLetters[0];
            size_t selectedLetter = 0;
            for (size_t letter = 0; letter < alphabetSize; ++letter)
            {
                if (usedLetters[letter] < minCount)
                {
                    minCount = usedLetters[letter];
                    selectedLetter = letter;
                }
            }
            replaceData[index] = static_cast<char>(alphabetStart + selectedLetter);
            ++usedLetters[selectedLetter];
        }
        std::ranges::sort(replaceData);
        std::string result(s);
        for (size_t index = 0, replaceDataIndex = 0; (index < result.size()) && (replaceDataIndex < replaceData.size()); ++index)
        {
            if (result[index] == '?')
                result[index] = replaceData[replaceDataIndex++];
        }
        return result;
    }
};

}

namespace ReplaceQMarksInStringMinItsValueTask
{

TEST(ReplaceQMarksInStringMinItsValueTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("abc", solution.minimizeStringValue("???"));
    ASSERT_EQ("abac", solution.minimizeStringValue("a?a?"));
}

TEST(ReplaceQMarksInStringMinItsValueTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("abcdefghijklmnopqrstuvwxyaz", solution.minimizeStringValue("abcdefghijklmnopqrstuvwxy??"));
}

}