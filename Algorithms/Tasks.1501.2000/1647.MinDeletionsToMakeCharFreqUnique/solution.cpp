#include <algorithm>
#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{
class Solution
{
public:
    [[nodiscard]] int minDeletions(std::string const &s) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::array<size_t, alphabetSize> letters{};
        letters.fill(0);
        for (const char ch : s)
            ++letters[ch - alphabetStart];
        std::sort(letters.begin(), letters.end(), std::greater<>());
        size_t deletionCount = 0;
        for (size_t index = 1; index < alphabetSize; ++index)
        {
            if (letters[index] == 0)
                break;
            if (letters[index] == letters[index - 1])
            {
                size_t current = index;
                while ((current < alphabetSize) && (letters[current] == letters[index - 1]))
                {
                    --letters[current];
                    ++deletionCount;
                    ++current;
                }
            }
        }
        return static_cast<int>(deletionCount);
    }
};

}

namespace MinDeletionsToMakeCharFreqUniqueTask
{

TEST(MinDeletionsToMakeCharFreqUniqueTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minDeletions("aab"));
    ASSERT_EQ(2, solution.minDeletions("aaabbbcc"));
    ASSERT_EQ(2, solution.minDeletions("ceabaacb"));
}

TEST(MinDeletionsToMakeCharFreqUniqueTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minDeletions("abcabc"));
}

}