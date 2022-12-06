#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int appendCharacters(std::string const &s, std::string const &t) const
    {
        size_t tIndex = 0;
        for (size_t sIndex = 0; (sIndex < s.size()) && (tIndex < t.size()); ++sIndex)
        {
            if (t[tIndex] == s[sIndex])
                ++tIndex;
        }
        return static_cast<int>(t.size() - tIndex);
    }
};

}

namespace AppendCharsToStringToMakeSubseqTask
{

TEST(AppendCharsToStringToMakeSubseqTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.appendCharacters("coaching", "coding"));
    ASSERT_EQ(0, solution.appendCharacters("abcde", "a"));
    ASSERT_EQ(5, solution.appendCharacters("z", "abcde"));
}

}