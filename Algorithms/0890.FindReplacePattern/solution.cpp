#include <algorithm>
#include <array>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> findAndReplacePattern(std::vector<std::string> const &words, std::string const &pattern) const
    {
        std::vector<std::string> result;
        std::copy_if(words.cbegin(), words.cend(), std::back_inserter(result), [this, &pattern](std::string const &word){ return isMatch(word, pattern); });
        return result;
    }

private:
    bool isMatch(std::string const &word, std::string const &pattern) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::array<char, alphabetSize> wordPatternMap{};
        std::array<char, alphabetSize> patternWordMap{};
        wordPatternMap.fill(0);
        patternWordMap.fill(0);
        for (size_t index = 0; index < word.size(); ++index)
        {
            if (wordPatternMap[word[index] - alphabetStart] == 0 && patternWordMap[pattern[index] - alphabetStart] == 0)
            {
                wordPatternMap[word[index] - alphabetStart] = pattern[index];
                patternWordMap[pattern[index] - alphabetStart] = word[index];
            }
            if (wordPatternMap[word[index] - alphabetStart] != pattern[index] || patternWordMap[pattern[index] - alphabetStart] != word[index])
                return false;
        }
        return true;
    }
};

}

namespace FindReplacePatternTask
{

TEST(FindReplacePatternTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"mee", "aqq"}), solution.findAndReplacePattern({"abc", "deq", "mee", "aqq", "dkd", "ccc"}, "abb"));
    ASSERT_EQ(std::vector<std::string>({"a", "b", "c"}), solution.findAndReplacePattern({"a", "b", "c"}, "a"));
}

}