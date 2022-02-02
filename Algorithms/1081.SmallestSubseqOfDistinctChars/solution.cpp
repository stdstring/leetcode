#include <algorithm>
#include <queue>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string smallestSubsequence(std::string const &s) const
    {
        // preparation
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::vector<std::queue<size_t>> charIndices(alphabetSize);
        for (size_t index = 0; index < s.size(); ++index)
            charIndices[s[index] - alphabetStart].push(index);
        std::vector<std::pair<size_t, size_t>> lastIndices;
        for (size_t index = 0; index < alphabetSize; ++index)
        {
            if (!charIndices[index].empty())
                lastIndices.emplace_back(index, charIndices[index].back());
        }
        std::sort(lastIndices.begin(), lastIndices.end(), [](std::pair<size_t, size_t> const &left, std::pair<size_t, size_t> const &right){ return left.second < right.second; });
        // calculation
        std::string result;
        size_t usedLetters = 0;
        size_t currentIndex = 0;
        for (std::pair<size_t, size_t> const &lastIndex : lastIndices)
        {
            if ((usedLetters & (1LL << lastIndex.first)) != 0)
                continue;
            for (size_t letterIndex = 0; letterIndex <= lastIndex.first; ++letterIndex)
            {
                if ((usedLetters & (1LL << letterIndex)) != 0)
                    continue;
                while (!charIndices[letterIndex].empty() && charIndices[letterIndex].front() < currentIndex)
                    charIndices[letterIndex].pop();
                if (charIndices[letterIndex].empty())
                    continue;
                if (charIndices[letterIndex].front() > lastIndex.second)
                    continue;
                result.push_back(static_cast<char>(letterIndex + alphabetStart));
                currentIndex = charIndices[letterIndex].front() + 1;
                charIndices[letterIndex].pop();
                usedLetters |= (1LL << letterIndex);
            }
        }
        return result;
    }
};

}

namespace SmallestSubseqOfDistinctCharsTask
{

TEST(SmallestSubseqOfDistinctCharsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("abc", solution.smallestSubsequence("bcabc"));
    ASSERT_EQ("acdb", solution.smallestSubsequence("cbacdcbc"));
}

TEST(SmallestSubseqOfDistinctCharsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("abcdef", solution.smallestSubsequence("bdfecedcbfcfeaaffdbaeeabadbbbddddcafdfeeeebfcdabcfaadecddccdefcabedbebbdcbdfefeffcbbeaefaeefeeceadea"));
}

}