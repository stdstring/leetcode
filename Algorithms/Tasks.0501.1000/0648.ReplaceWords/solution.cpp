#include <cmath>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string replaceWords(std::vector<std::string> const &dictionary, std::string const &sentence) const
    {
        std::vector<std::vector<int>> dictionaryTrie;
        fillDictionaryTrie(dictionary, dictionaryTrie);
        std::string result;
        bool hasRoot = false;
        size_t node = 0;
        for (char ch : sentence)
        {
            if (ch == ' ')
            {
                result.push_back(ch);
                node = 0;
                hasRoot = false;
            }
            else if (hasRoot)
                /* do nothing */;
            else if (node == dictionaryTrie.size())
                result.push_back(ch);
            else
            {
                const size_t charIndex = ch - AlphabetStart;
                hasRoot = dictionaryTrie[node][charIndex] < 0;
                node = dictionaryTrie[node][charIndex] > 0 ? dictionaryTrie[node][charIndex] : dictionaryTrie.size();
                result.push_back(ch);
            }
        }
        return result;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    void fillDictionaryTrie(std::vector<std::string> const &dictionary, std::vector<std::vector<int>> &dictionaryTrie) const
    {
        constexpr int wordEndNode = INT_MIN;
        dictionaryTrie.emplace_back(AlphabetSize, 0);
        for (std::string const& root : dictionary)
        {
            size_t node = 0;
            for (size_t index = 0; index < root.size(); ++index)
            {
                const char ch = root[index];
                const size_t charIndex = ch - AlphabetStart;
                if (index == root.size() - 1)
                    dictionaryTrie[node][charIndex] = dictionaryTrie[node][charIndex] == 0 || dictionaryTrie[node][charIndex] == wordEndNode ? wordEndNode : -std::abs(dictionaryTrie[node][charIndex]);
                else if (dictionaryTrie[node][charIndex] == 0 || dictionaryTrie[node][charIndex] == wordEndNode)
                {
                    dictionaryTrie[node][charIndex] = (dictionaryTrie[node][charIndex] == 0 ? 1 : -1) * static_cast<int>(dictionaryTrie.size());
                    node = dictionaryTrie.size();
                    dictionaryTrie.emplace_back(AlphabetSize, 0);
                }
                else
                    node = std::abs(dictionaryTrie[node][charIndex]);
            }
        }
    }
};

}

namespace ReplaceWordsTask
{

TEST(ReplaceWordsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("the cat was rat by the bat", solution.replaceWords({"cat", "bat", "rat"}, "the cattle was rattled by the battery"));
    ASSERT_EQ("a a b c", solution.replaceWords({"a", "b", "c"}, "aadsfasf absbs bbab cadsfafs"));
    ASSERT_EQ("a a a a a a a a bbb baba a", solution.replaceWords({"a", "aa", "aaa", "aaaa"}, "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa"));
    ASSERT_EQ("the cat was rat by the bat", solution.replaceWords({"catt", "cat", "bat", "rat"}, "the cattle was rattled by the battery"));
    ASSERT_EQ("it is ab that this solution is ac", solution.replaceWords({"ac", "ab"}, "it is abnormal that this solution is accepted"));
}

}