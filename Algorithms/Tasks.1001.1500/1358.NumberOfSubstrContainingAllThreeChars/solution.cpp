#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfSubstrings(std::string const &s) const
    {
        constexpr size_t npos = -1;
        size_t substringsCount = 0;
        size_t nearestAIndex = npos;
        size_t nearestBIndex = npos;
        size_t nearestCIndex = npos;
        for (size_t rIndex = 0; rIndex < s.size(); ++rIndex)
        {
            switch (s[s.size() - 1 - rIndex])
            {
                case 'a':
                    nearestAIndex = rIndex;
                    break;
                case 'b':
                    nearestBIndex = rIndex;
                    break;
                case 'c':
                    nearestCIndex = rIndex;
                    break;
                default:
                    break;
            }
            if (nearestAIndex != npos && nearestBIndex != npos && nearestCIndex != npos)
                substringsCount += (std::min({nearestAIndex, nearestBIndex, nearestCIndex}) + 1);
        }
        return static_cast<int>(substringsCount);
    }
};

}

namespace NumberOfSubstrContainingAllThreeCharsTask
{

TEST(NumberOfSubstrContainingAllThreeCharsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(10, solution.numberOfSubstrings("abcabc"));
    ASSERT_EQ(3, solution.numberOfSubstrings("aaacb"));
    ASSERT_EQ(1, solution.numberOfSubstrings("abc"));
}

}