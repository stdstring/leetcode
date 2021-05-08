#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{

public:
    int numMatchingSubseq(std::string const &s, std::vector<std::string> const &words) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr char firstLetter = 'a';
        std::unordered_map<char, std::queue<std::pair<size_t, size_t>>> wordsMap;
        for (size_t letterIndex = 0; letterIndex < alphabetSize; ++letterIndex)
            wordsMap.emplace(static_cast<char>(firstLetter + letterIndex), std::queue<std::pair<size_t, size_t>>());
        for (size_t index = 0; index < words.size(); ++index)
            wordsMap[words[index][0]].emplace(index, 0);
        size_t matchingSubseqCount = 0;
        for (char ch : s)
        {
            const size_t queueSize = wordsMap[ch].size();
            for (size_t index = 0; index < queueSize; ++index)
            {
                const size_t wordIndex = wordsMap[ch].front().first;
                const size_t charIndex = wordsMap[ch].front().second;
                if (charIndex == (words[wordIndex].size() - 1))
                    ++matchingSubseqCount;
                else
                    wordsMap[words[wordIndex][charIndex + 1]].emplace(wordIndex, charIndex + 1);
                wordsMap[ch].pop();
            }
        }
        return static_cast<int>(matchingSubseqCount);
    }
};

}

namespace NumberOfMatchingSubsequencesTask
{

TEST(NumberOfMatchingSubsequencesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.numMatchingSubseq("abcde", {"a", "bb", "acd", "ace"}));
    ASSERT_EQ(2, solution.numMatchingSubseq("dsahjpjauf", {"ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"}));
}

}