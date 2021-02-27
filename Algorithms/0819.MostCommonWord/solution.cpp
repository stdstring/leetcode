#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string mostCommonWord(std::string const &paragraph, std::vector<std::string> const &banned) const
    {
        const std::unordered_set<std::string> bannedWords(banned.cbegin(), banned.cend());
        std::unordered_map<std::string, size_t> words;
        size_t pos = 0;
        while (pos < paragraph.size())
        {
            const size_t afterEndPos = moveAfterWordFinish(paragraph, pos);
            std::string word(paragraph.substr(pos, afterEndPos - pos));
            std::transform(word.cbegin(), word.cend(), word.begin(), [](unsigned char ch){ return std::tolower(ch); });
            if (bannedWords.count(word) == 0)
                words[word] += 1;
            pos = moveToWordStart(paragraph, afterEndPos);
        }
        std::string bestWord;
        size_t bestCount = 0;
        for (auto const &entry : words)
        {
            if (entry.second > bestCount)
            {
                bestWord = entry.first;
                bestCount = entry.second;
            }
        }
        return bestWord;
    }

private:
    size_t moveToWordStart(std::string const &paragraph, size_t pos) const
    {
        while ((pos < paragraph.size()) && !std::isalpha(paragraph[pos]))
            ++pos;
        return pos;
    }

    size_t moveAfterWordFinish(std::string const &paragraph, size_t pos) const
    {
        while ((pos < paragraph.size()) && std::isalpha(paragraph[pos]))
            ++pos;
        return pos;
    }
};

}

namespace MostCommonWordTask
{

TEST(MostCommonWordTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("ball", solution.mostCommonWord("Bob hit a ball, the hit BALL flew far after it was hit.", {"hit"}));
}

}