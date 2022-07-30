#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool repeatedSubstringPattern(std::string const &s) const
    {
        for (size_t prefixSize = 1; prefixSize <= s.size() / 2; ++prefixSize)
        {
            if (checkPrefix(s, prefixSize))
                return true;
        }
        return false;
    }

    [[nodiscard]] bool repeatedSubstringPatternAlt(std::string const &s) const
    {
        return (s + s).substr(1, 2 * s.size() - 2).find(s) != std::string::npos;
    }

private:
    [[nodiscard]] bool checkPrefix(std::string const &source, size_t prefixSize) const
    {
        if ((source.size() % prefixSize) != 0)
            return false;
        for (size_t index = prefixSize; index < source.size(); ++index)
        {
            if (source[index] != source[index % prefixSize])
                return false;
        }
        return true;
    }
};

}

namespace
{

void checkRepeatedSubstringPattern(std::string const &source, bool expexted)
{
    constexpr Solution solution;
    ASSERT_EQ(expexted, solution.repeatedSubstringPattern(source));
    ASSERT_EQ(expexted, solution.repeatedSubstringPatternAlt(source));
}

}

namespace RepeatedSubstringPatternTask
{

TEST(RepeatedSubstringPatternTaskTests, Examples)
{
    checkRepeatedSubstringPattern("abab", true);
    checkRepeatedSubstringPattern("aba", false);
    checkRepeatedSubstringPattern("abcabcabcabc", true);
}

TEST(RepeatedSubstringPatternTaskTests, FromWrongAnswers)
{
    checkRepeatedSubstringPattern("abaababaab", true);
    checkRepeatedSubstringPattern("babbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbbbabbaaabbb", true);
}

}