#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> uncommonFromSentences(std::string const &s1, std::string const &s2) const
    {
        std::unordered_map<std::string, size_t> words;
        splitWords(s1, words);
        splitWords(s2, words);
        std::vector<std::string> result;
        for (auto const &[word, count] : words)
        {
            if (count == 1)
                result.emplace_back(word);
        }
        std::ranges::sort(result);
        return result;
    }

private:
    void splitWords(std::string const &source, std::unordered_map<std::string, size_t> &words) const
    {
        for (size_t index = 0; index < source.size();)
        {
            size_t space = source.find(' ', index);
            if (space == std::string::npos)
                space = source.size();
            ++words[source.substr(index, space - index)];
            index = space + 1;
        }
    }
};

}

namespace UncommonWordsFromTwoSentencesTask
{

TEST(UncommonWordsFromTwoSentencesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"sour", "sweet"}), solution.uncommonFromSentences("this apple is sweet", "this apple is sour"));
    ASSERT_EQ(std::vector<std::string>({"banana"}), solution.uncommonFromSentences("apple apple", "banana"));
}

}