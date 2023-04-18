#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numWays(std::vector<std::string> const &words, std::string const &target) const
    {
        constexpr size_t modValue = 1000000007;
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        const size_t wordSize = words.front().size();
        if (target.size() > wordSize)
            return 0;
        std::vector<std::vector<size_t>> lettersData(wordSize, std::vector<size_t>(alphabetSize, 0));
        for (std::string const &word : words)
        {
            for (size_t index = 0; index < wordSize; ++index)
                ++lettersData[index][word[index] - alphabetStart];
        }
        std::vector<size_t> dpPrefixSumsCurrentRow(wordSize, 0);
        for (size_t wordsIndex = 0; wordsIndex <= wordSize - target.size(); ++wordsIndex)
        {
            const size_t letterCount = lettersData[wordsIndex][target.front() - alphabetStart];
            dpPrefixSumsCurrentRow[wordsIndex] = ((wordsIndex > 0 ? dpPrefixSumsCurrentRow[wordsIndex - 1] : 0) + letterCount) % modValue;
        }
        for (size_t targetIndex = 1; targetIndex < target.size(); ++targetIndex)
        {
            std::vector<size_t> dpPrefixSumsNextRow(wordSize, 0);
            for (size_t wordsIndex = targetIndex; wordsIndex <= wordSize - target.size() + targetIndex; ++wordsIndex)
            {
                const size_t letterCount = lettersData[wordsIndex][target[targetIndex] - alphabetStart];
                dpPrefixSumsNextRow[wordsIndex] = (dpPrefixSumsNextRow[wordsIndex - 1] + dpPrefixSumsCurrentRow[wordsIndex - 1] * letterCount) % modValue;
            }
            std::swap(dpPrefixSumsCurrentRow, dpPrefixSumsNextRow);
        }
        return static_cast<int>(dpPrefixSumsCurrentRow.back());
    }
};

}

namespace NumberWaysFormTargetStringGivenDictTask
{

TEST(NumberWaysFormTargetStringGivenDictTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.numWays({"acca", "bbbb", "caca"}, "aba"));
    ASSERT_EQ(4, solution.numWays({"abba", "baab"}, "bab"));
}

TEST(NumberWaysFormTargetStringGivenDictTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.numWays({ "acca", "caca" }, "abbba"));
}

}