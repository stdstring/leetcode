#include <array>
#include <memory>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> sumPrefixScores(std::vector<std::string> const &words) const
    {
        std::shared_ptr<TrieNode> trieRoot = std::make_shared<TrieNode>();
        for (std::string const &word : words)
        {
            TrieNode *currentNode = trieRoot.get();
            for (const char ch : word)
            {
                const size_t charIndex = ch - AlphabetStart;
                ++currentNode->PrefixCost[charIndex];
                if (!currentNode->Next[charIndex])
                    currentNode->Next[charIndex] = new TrieNode();
                currentNode = currentNode->Next[charIndex];
            }
        }
        std::vector<int> result(words.size(), 0);
        for (size_t index = 0; index < words.size(); ++index)
        {
            TrieNode *currentNode = trieRoot.get();
            for (const char ch : words[index])
            {
                const size_t charIndex = ch - AlphabetStart;
                result[index] += currentNode->PrefixCost[charIndex];
                currentNode = currentNode->Next[charIndex];
            }
        }
        return result;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    struct TrieNode
    {
        TrieNode()
        {
            Next.fill(nullptr);
            PrefixCost.fill(0);
        }

        ~TrieNode()
        {
            for (const TrieNode* child : Next)
                delete child;
        }

        // We don't use std::shared_ptr because I had MLE on test data when I used std::shared_ptr
        std::array<TrieNode*, AlphabetSize> Next;
        std::array<int, AlphabetSize> PrefixCost;
    };
};

}

namespace SumOfPrefixScoresOfStringsTask
{

TEST(SumOfPrefixScoresOfStringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({5, 4, 3, 2}), solution.sumPrefixScores({"abc", "ab", "bc", "b"}));
    ASSERT_EQ(std::vector<int>({4}), solution.sumPrefixScores({"abcd"}));
}

}