#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestSemiRepetitiveSubstring(std::string const &s) const
    {
        size_t bestSize = 1;
        bool hasSameDigitPair = false;
        size_t start = 0;
        for (size_t index = 1; index < s.size(); ++index)
        {
            if (s[index] == s[index - 1])
            {
                while (hasSameDigitPair)
                {
                    if (s[start] == s[start + 1])
                        hasSameDigitPair = false;
                    ++start;
                }
                hasSameDigitPair = true;
            }
            bestSize = std::max(bestSize, index - start + 1);
        }
        return static_cast<int>(bestSize);
    }
};

}

namespace FindLongestSemiRepetitiveSubstringTask
{

TEST(FindLongestSemiRepetitiveSubstringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.longestSemiRepetitiveSubstring("52233"));
    ASSERT_EQ(4, solution.longestSemiRepetitiveSubstring("5494"));
    ASSERT_EQ(2, solution.longestSemiRepetitiveSubstring("1111111"));
}

}