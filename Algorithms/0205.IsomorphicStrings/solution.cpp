#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isIsomorphic(std::string const &s, std::string const &t) const
    {
        std::array<char, UCHAR_MAX + 1> firstSecondMap;
        firstSecondMap.fill(0);
        std::array<char, UCHAR_MAX + 1> secondFirstMap;
        secondFirstMap.fill(0);
        for(size_t index = 0; index < s.size(); ++index)
        {
            if (firstSecondMap[s[index]] == 0 && secondFirstMap[t[index]] == 0)
            {
                firstSecondMap[s[index]] = t[index];
                secondFirstMap[t[index]] = s[index];
            }
            else if (firstSecondMap[s[index]] != t[index] || secondFirstMap[t[index]] != s[index])
                return false;
        }
        return true;
    }
};

}

namespace IsomorphicStringsTask
{

TEST(IsomorphicStringsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isIsomorphic("egg", "add"));
    ASSERT_EQ(false, solution.isIsomorphic("foo", "bar"));
    ASSERT_EQ(true, solution.isIsomorphic("paper", "title"));
}

TEST(IsomorphicStringsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isIsomorphic("ab", "aa"));
}

}