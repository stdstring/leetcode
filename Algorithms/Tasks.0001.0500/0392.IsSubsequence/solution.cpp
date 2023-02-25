#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isSubsequence(std::string const &s, std::string const &t) const
    {
        size_t sIndex = 0;
        for (char ch : t)
        {
            if (s[sIndex] == ch)
                ++sIndex;
            if (sIndex == s.size())
                return true;
        }
        return sIndex == s.size();
    }
};

}

namespace IsSubsequenceTask
{

TEST(IsSubsequenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isSubsequence("abc", "ahbgdc"));
    ASSERT_EQ(false, solution.isSubsequence("axc", "ahbgdc"));
}

TEST(IsSubsequenceTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isSubsequence("", ""));
}

}