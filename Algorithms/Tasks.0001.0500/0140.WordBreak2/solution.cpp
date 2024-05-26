#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> wordBreak(std::string const &s, std::vector<std::string> const &wordDict) const
    {
        std::unordered_set<std::string> words;
        words.reserve(wordDict.size());
        size_t maxWordSize = 0;
        for (std::string const& word : wordDict)
        {
            words.emplace(word);
            maxWordSize = std::max(maxWordSize, word.size());
        }
        std::string currentSentence;
        std::vector<std::string> result;
        collectSentences(s, 0, words, maxWordSize, currentSentence, result);
        return result;
    }

private:
    void collectSentences(std::string const &source,
                          size_t sourceIndex,
                          std::unordered_set<std::string> const &words,
                          size_t maxWordSize,
                          std::string &currentSentence,
                          std::vector<std::string> &sentences) const
    {
        if (sourceIndex == source.size())
        {
            sentences.emplace_back(currentSentence);
            return;
        }
        std::string currentPart;
        const size_t maxAvailableSize = std::min(maxWordSize, source.size() - sourceIndex);
        currentPart.reserve(maxAvailableSize);
        for (size_t size = 1; size <= maxAvailableSize; ++size)
        {
            const size_t currentIndex = sourceIndex + size - 1;
            currentPart.push_back(source[currentIndex]);
            if (words.contains(currentPart))
            {
                if (sourceIndex > 0)
                    currentSentence.push_back(' ');
                currentSentence.append(currentPart);
                collectSentences(source, sourceIndex + currentPart.size(), words, maxWordSize, currentSentence, sentences);
                removeBack(currentSentence, currentPart.size() + (sourceIndex > 0 ? 1 : 0));
            }
        }
    }

    void removeBack(std::string &dest, size_t count) const
    {
        for (size_t index = 0; index < count; ++index)
            dest.pop_back();
    }
};

}

namespace WordBreak2Task
{

TEST(WordBreak2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"cat sand dog", "cats and dog"}),
              solution.wordBreak("catsanddog", {"cat", "cats", "and", "sand", "dog"}));
    ASSERT_EQ(std::vector<std::string>({"pine apple pen apple", "pine applepen apple", "pineapple pen apple"}),
              solution.wordBreak("pineapplepenapple", {"apple", "pen", "applepen", "pine", "pineapple"}));
    ASSERT_EQ(std::vector<std::string>(), solution.wordBreak("catsandog", {"cats", "dog", "sand", "and", "cat"}));
}

}