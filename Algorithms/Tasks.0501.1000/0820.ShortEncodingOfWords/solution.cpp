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
    int minimumLengthEncoding(std::vector<std::string> const &words) const
    {
        std::vector<std::string> sortedWords(words);
        std::sort(sortedWords.begin(), sortedWords.end(), [](std::string const &left, std::string const &right){ return left.size() < right.size(); });
        std::unordered_set<std::string> knownWords;
        size_t totalSize = 0;
        for (std::string const &word : sortedWords)
        {
            totalSize += (word.size() + 1);
            if (!knownWords.empty())
            {
                std::string reversedWord(word.crbegin(), word.crend());
                while (!reversedWord.empty() && knownWords.count(reversedWord) == 0)
                    reversedWord.pop_back();
                if (!reversedWord.empty())
                {
                    knownWords.erase(reversedWord);
                    totalSize -= (reversedWord.size() + 1);
                }
            }
            knownWords.insert(std::string(word.crbegin(), word.crend()));
        }
        return static_cast<int>(totalSize);
    }
};

}

namespace ShortEncodingOfWordsTask
{

TEST(ShortEncodingOfWordsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(10, solution.minimumLengthEncoding({"time", "me", "bell"}));
    ASSERT_EQ(2, solution.minimumLengthEncoding({"t"}));
}

TEST(ShortEncodingOfWordsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(5, solution.minimumLengthEncoding({"time", "time", "time", "time"}));
    ASSERT_EQ(12, solution.minimumLengthEncoding({"time", "atime", "btime"}));
}

}