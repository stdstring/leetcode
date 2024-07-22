#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool doesAliceWin(std::string const &s) const
    {
        return std::ranges::any_of(s, [this](char ch){ return isVowel(ch); });
    }

private:
    [[nodiscard]] bool isVowel(char ch) const
    {
        return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u');
    }
};

}

namespace VowelsGameInStringTask
{

TEST(VowelsGameInStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.doesAliceWin("leetcoder"));
    ASSERT_EQ(false, solution.doesAliceWin("bbcd"));
}

}