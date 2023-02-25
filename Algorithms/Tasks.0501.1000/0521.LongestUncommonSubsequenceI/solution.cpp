#include <string>
#include <utility>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findLUSlength(std::string const &a, std::string const &b) const
    {
        return (a.size() == b.size()) && (a == b) ? -1 : static_cast<int>(std::max(a.size(), b.size()));
    }
};

}

namespace LongestUncommonSubsequenceITask
{

TEST(LongestUncommonSubsequenceITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.findLUSlength("aba", "cdc"));
    ASSERT_EQ(3, solution.findLUSlength("aaa", "bbb"));
    ASSERT_EQ(-1, solution.findLUSlength("aaa", "aaa"));
}

TEST(LongestUncommonSubsequenceITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(17, solution.findLUSlength("aefawfawfawfaw", "aefawfeawfwafwaef"));
    ASSERT_EQ(3, solution.findLUSlength("aab", "aba"));
}

}