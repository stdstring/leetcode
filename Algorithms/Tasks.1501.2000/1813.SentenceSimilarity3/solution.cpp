#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool areSentencesSimilar(std::string const &sentence1, std::string const &sentence2) const
    {
        std::vector<std::string> words1(splitSentence(sentence1));
        std::vector<std::string> words2(splitSentence(sentence2));
        if (words1.size() > words2.size())
            std::swap(words1, words2);
        size_t largestCommonPrefix = 0;
        for (size_t index = 0; (index < words1.size()) && (words1[index] == words2[index]); ++index)
            ++largestCommonPrefix;
        if (words1.size() == largestCommonPrefix)
            return true;
        size_t largestCommonSuffix = 0;
        for (size_t index = 0; (index < words1.size()) && (words1[words1.size() - 1 -index] == words2[words2.size() - 1 - index]); ++index)
            ++largestCommonSuffix;
        if (words1.size() == largestCommonSuffix)
            return true;
        return (largestCommonPrefix + largestCommonSuffix) >= words1.size();
    }

private:
    [[nodiscard]] std::vector<std::string> splitSentence(std::string const &sentence) const
    {
        std::vector<std::string> words;
        size_t start = 0;
        for (size_t separatorPos = sentence.find(' ', start); separatorPos != std::string::npos; separatorPos = sentence.find(' ', start))
        {
            words.push_back(sentence.substr(start, separatorPos - start));
            start = separatorPos + 1;
        }
        words.push_back(sentence.substr(start));
        return words;
    }
};

}

namespace SentenceSimilarity3Task
{

TEST(SentenceSimilarity3TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.areSentencesSimilar("My name is Haley", "My Haley"));
    ASSERT_EQ(false, solution.areSentencesSimilar("of", "A lot of words"));
    ASSERT_EQ(true, solution.areSentencesSimilar("Eating right now", "Eating"));
}

TEST(SentenceSimilarity3TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.areSentencesSimilar("A", "a A b A"));
    ASSERT_EQ(false, solution.areSentencesSimilar("Luky", "Lucccky"));
}

}