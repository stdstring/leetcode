#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int wordCount(std::vector<std::string> const &startWords, std::vector<std::string> const &targetWords) const
    {
        std::unordered_map<int, size_t> targetNumbers;
        for (std::string const &word : targetWords)
            targetNumbers[createWordRepresentation(word)] += 1;
        size_t targetWordsCount = 0;
        for (std::string const &word : startWords)
        {
            const int number = createWordRepresentation(word);
            for (size_t letter = 0; letter < AlphabetSize; ++letter)
            {
                int possibleTarget = number | (1 << letter);
                const auto iterator = targetNumbers.find(possibleTarget);
                if ((possibleTarget != number) && (iterator != targetNumbers.cend()))
                {
                    targetWordsCount += iterator->second;
                    targetNumbers.erase(iterator);
                }
            }
        }
        return static_cast<int>(targetWordsCount);
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    int createWordRepresentation(std::string const &word) const
    {
        int result = 0;
        for (char ch : word)
            result |= (1 << (ch - AlphabetStart));
        return result;
    }
};

}

namespace CountWordsObtainedAfterAddingLetterTask
{

TEST(CountWordsObtainedAfterAddingLetterTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.wordCount({"ant", "act", "tack"}, {"tack", "act", "acti"}));
    ASSERT_EQ(1, solution.wordCount({"ab", "a"}, {"abc", "abcd"}));
}

TEST(CountWordsObtainedAfterAddingLetterTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(4, solution.wordCount({"obmcx", "r", "bqxc", "f", "tijlu", "mpbk", "vxh", "ue", "x", "rb"},
                                    {"kf", "sxqbc", "rq", "z", "j", "rft", "oxcbms", "g", "rdnq", "qmc", "nzbq"}));
    ASSERT_EQ(2, solution.wordCount({"o"}, {"ot", "ot"}));
}

}