#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string findLongestWord(std::string const &s, std::vector<std::string> const &dictionary) const
    {
        std::string bestWord;
        for (std::string const &word : dictionary)
        {
            if (word.size() < bestWord.size())
                continue;
            size_t sourceIndex = 0;
            size_t wordIndex = 0;
            while (sourceIndex < s.size() && wordIndex < word.size())
            {
                if (s[sourceIndex] == word[wordIndex])
                    ++wordIndex;
                ++sourceIndex;
            }
            if (wordIndex != word.size())
                continue;
            if (bestWord.size() < word.size() || (bestWord.size() == word.size() && word < bestWord))
                bestWord = word;
        }
        return bestWord;
    }
};

}

namespace LongestWordInDictThroughDeletingTask
{

TEST(LongestWordInDictThroughDeletingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("apple", solution.findLongestWord("abpcplea", {"ale", "apple", "monkey", "plea"}));
    ASSERT_EQ("a", solution.findLongestWord("abpcplea", {"a", "b", "c"}));
}

}