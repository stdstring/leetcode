#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string reverseWords(std::string const &s) const
    {
        std::vector<std::string> words;
        size_t index = skipWhitespaces(s, 0);
        while (index < s.size())
        {
            words.emplace_back("");
            while (index < s.size() && s[index] != ' ')
                words.back().push_back(s[index++]);
            index = skipWhitespaces(s, index);
        }
        return buildResult(words);
    }

private:
    size_t skipWhitespaces(std::string const &s, size_t index) const
    {
        while (index < s.size() && s[index] == ' ')
            ++index;
        return index;
    }

    std::string buildResult(std::vector<std::string> const &words) const
    {
        std::string dest;
        for (size_t index = 0; index < words.size(); ++index)
        {
            if (!dest.empty())
                dest.push_back(' ');
            dest.append(words[words.size() - 1 - index]);
        }
        return dest;
    }
};

}

namespace ReverseWordsInStringTask
{

TEST(ReverseWordsInStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("blue is sky the", solution.reverseWords("the sky is blue"));
    ASSERT_EQ("world! hello", solution.reverseWords("  hello world!  "));
    ASSERT_EQ("example good a", solution.reverseWords("a good   example"));
}

}