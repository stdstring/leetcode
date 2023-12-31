#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxLengthBetweenEqualCharacters(std::string const &s) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        size_t maxLength = s.size();
        std::vector<size_t> firstIndices(alphabetSize, s.size());
        for (size_t index = 0; index < s.size(); ++index)
        {
            size_t ch = s[index] - alphabetStart;
            if (firstIndices[ch] != s.size())
                maxLength = std::max(index - firstIndices[ch] - 1, maxLength == s.size() ? 0 : maxLength);
            else
                firstIndices[ch] = index;
        }
        return maxLength == s.size() ? -1 : static_cast<int>(maxLength);
    }
};

}

namespace LargestSubstringBetweenTwoEqualCharsTask
{

TEST(LargestSubstringBetweenTwoEqualCharsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.maxLengthBetweenEqualCharacters("aa"));
    ASSERT_EQ(2, solution.maxLengthBetweenEqualCharacters("abca"));
    ASSERT_EQ(-1, solution.maxLengthBetweenEqualCharacters("cbzxy"));
}

TEST(LargestSubstringBetweenTwoEqualCharsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxLengthBetweenEqualCharacters("ababa"));
}

TEST(LargestSubstringBetweenTwoEqualCharsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(18, solution.maxLengthBetweenEqualCharacters("mgntdygtxrvxjnwksqhxuxtrv"));
}

}