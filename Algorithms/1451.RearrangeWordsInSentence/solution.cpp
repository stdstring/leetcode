#include <cctype>
#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string arrangeWords(std::string const &text) const
    {
        std::map<size_t, std::vector<std::string>> wordsMap;
        std::string currentWord;
        for (const char ch : text)
        {
            if (ch == ' ')
            {
                wordsMap[currentWord.size()].push_back(currentWord);
                currentWord.clear();
            }
            else
                currentWord.push_back(static_cast<char>(std::tolower(ch)));
        }
        wordsMap[currentWord.size()].push_back(currentWord);
        std::string result;
        for (const auto& [size, words] : wordsMap)
        {
            for (std::string const &word : words)
            {
                if (!result.empty())
                    result.push_back(' ');
                result.append(word);
            }
        }
        result[0] = static_cast<char>(std::toupper(result[0]));
        return result;
    }
};

}

namespace RearrangeWordsInSentenceTask
{

TEST(RearrangeWordsInSentenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("Is cool leetcode", solution.arrangeWords("Leetcode is cool"));
    ASSERT_EQ("On and keep calm code", solution.arrangeWords("Keep calm and code on"));
    ASSERT_EQ("To be or to be not", solution.arrangeWords("To be or not to be"));
}

}