#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string longestWord(std::vector<std::string> const &words) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::vector<std::vector<size_t>> trie(1, std::vector<size_t>(26, 0));
        std::unordered_map<size_t, size_t> nodeWordMap;
        // create trie
        for (size_t index = 0; index < words.size(); ++index)
        {
            size_t currentNode = 0;
            for (char ch : words[index])
            {
                if (trie[currentNode][ch - alphabetStart] == 0)
                {
                    trie[currentNode][ch - alphabetStart] = trie.size();
                    trie.emplace_back(26, 0);
                }
                currentNode = trie[currentNode][ch - alphabetStart];
            }
            nodeWordMap.emplace(currentNode, index);
        }
        // find longest words
        std::vector<size_t> currentCandidates;
        std::vector<size_t> nextCandidates;
        for (size_t charIndex = 0; charIndex < alphabetSize; ++charIndex)
        {
            if (nodeWordMap.count(trie[0][charIndex]) == 1)
                nextCandidates.push_back(trie[0][charIndex]);
        }
        while (!nextCandidates.empty())
        {
            std::swap(currentCandidates, nextCandidates);
            nextCandidates.clear();
            for (size_t node : currentCandidates)
            {
                for (size_t charIndex = 0; charIndex < alphabetSize; ++charIndex)
                {
                    if (nodeWordMap.count(trie[node][charIndex]) == 1)
                        nextCandidates.push_back(trie[node][charIndex]);
                }
            }
        }
        // find best word
        if (currentCandidates.empty())
            return "";
        size_t bestWord = nodeWordMap[currentCandidates[0]];
        for (size_t index = 1; index < currentCandidates.size(); ++index)
        {
            const size_t currentWord = nodeWordMap[currentCandidates[index]];
            if (words[currentWord] < words[bestWord])
                bestWord = currentWord;
        }
        return words[bestWord];
    }
};

}

namespace LongestWordInDictionaryTask
{

TEST(LongestWordInDictionaryTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("world", solution.longestWord({"w", "wo", "wor", "worl", "world"}));
    ASSERT_EQ("apple", solution.longestWord({"a", "banana", "app", "appl", "ap", "apply", "apple"}));
}

TEST(LongestWordInDictionaryTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("", solution.longestWord({"wo", "wor", "worl", "world"}));
}

}