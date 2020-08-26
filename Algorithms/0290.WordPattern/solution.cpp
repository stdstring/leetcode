#include <array>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool wordPattern(std::string const &pattern, std::string const &str) const
    {
        std::array<std::string, AlphabetSize> usedWords;
        std::unordered_map<std::string, int> usedPatterns;
        size_t patternIndex = 0;
        size_t strIndex = 0;
        while (strIndex < str.size() && patternIndex < pattern.size())
        {
            int wordPattern = pattern[patternIndex] - 'a';
            std::string word = extractWord(str, strIndex);
            if (usedWords[wordPattern].empty())
            {
                if (usedPatterns.count(word) > 0)
                    return false;
                usedWords[wordPattern] = word;
                usedPatterns.emplace(word, wordPattern);
            }
            else
            {
                if (usedWords[wordPattern] != word || usedPatterns[word] != wordPattern)
                    return false;
            }
            ++patternIndex;
        }
        return (patternIndex >= pattern.size()) && (strIndex >= str.size());
    }

private:
    constexpr static int AlphabetSize = 26;

    std::string extractWord(std::string const &str, size_t &index) const
    {
        const size_t start = index;
        while (index < str.size() && str[index] != ' ')
            ++index;
        const size_t length = index - start;
        ++index;
        return str.substr(start, length);
    }
};

}

namespace WordPatternTask
{

TEST(WordPatternTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.wordPattern("abba", "dog cat cat dog"));
    ASSERT_EQ(false, solution.wordPattern("abba", "dog cat cat fish"));
    ASSERT_EQ(false, solution.wordPattern("aaaa", "dog cat cat dog"));
    ASSERT_EQ(false, solution.wordPattern("abba", "dog dog dog dog"));
}

TEST(WordPatternTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.wordPattern("aba", "cat cat cat dog"));
    ASSERT_EQ(false, solution.wordPattern("abc", "dog cat dog"));
}

}