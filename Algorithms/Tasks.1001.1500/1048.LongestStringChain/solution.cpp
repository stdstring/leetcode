#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestStrChain(std::vector<std::string> const &words) const
    {
        std::vector<size_t> wordIndices(words.size());
        std::iota(wordIndices.begin(), wordIndices.end(), 0);
        std::sort(wordIndices.begin(), wordIndices.end(), [&words](size_t left, size_t right){ return words[left].size() > words[right].size(); });
        std::unordered_map<std::string, size_t> wordIndexMap;
        for (size_t index = 0; index < wordIndices.size(); ++index)
            wordIndexMap[words[wordIndices[index]]] = index;
        size_t longestChainSize = 1;
        std::vector<size_t> chains(words.size(), 1);
        for (size_t index = 0; index < wordIndices.size(); ++index)
        {
            std::string const &currentWord = words[wordIndices[index]];
            std::string nextWord(currentWord, 1);
            for (size_t charIndex = 0; charIndex < currentWord.size(); ++charIndex)
            {
                std::unordered_map<std::string, size_t>::const_iterator iteratorMap = wordIndexMap.find(nextWord);
                if (iteratorMap != wordIndexMap.cend())
                {
                    chains[iteratorMap->second] = std::max(chains[iteratorMap->second], chains[index] + 1);
                    longestChainSize = std::max(longestChainSize, chains[iteratorMap->second]);
                }
                if (charIndex < nextWord.size())
                    nextWord[charIndex] = currentWord[charIndex];
            }
        }
        return static_cast<int>(longestChainSize);
    }
};

}

namespace LongestStringChainTask
{

TEST(LongestStringChainTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.longestStrChain({"a", "b", "ba", "bca", "bda", "bdca"}));
    ASSERT_EQ(5, solution.longestStrChain({"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"}));
    ASSERT_EQ(1, solution.longestStrChain({"abcd", "dbqca"}));
}

}