#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestContinuousSubstring(std::string const &s) const
    {
        constexpr size_t alphabetSize = 26;
        size_t bestSubstring = 1;
        size_t currentSubstring = 1;
        for (size_t index = 1; index < s.size(); ++index)
        {
            const char prev = s[index - 1];
            const char current = s[index];
            if ((prev + 1) == current)
                currentSubstring += 1;
            else
                currentSubstring = 1;
            bestSubstring = std::max(bestSubstring, currentSubstring);
            if (bestSubstring == alphabetSize)
                break;
        }
        return static_cast<int>(bestSubstring);
    }
};

}

namespace LengthOfLongestAlphContSubstrTask
{

TEST(LengthOfLongestAlphContSubstrTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.longestContinuousSubstring("abacaba"));
    ASSERT_EQ(5, solution.longestContinuousSubstring("abcde"));
}

TEST(LengthOfLongestAlphContSubstrTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.longestContinuousSubstring("z"));
}

}