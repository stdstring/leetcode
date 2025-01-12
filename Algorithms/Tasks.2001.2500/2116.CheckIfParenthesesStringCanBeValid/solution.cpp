#include <stack>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canBeValid(std::string const &s, std::string const &locked) const
    {
        if ((s.size() % 2) != 0 )
            return false;
        std::stack<size_t> unlockedChars;
        std::stack<size_t> lockedOpenBraces;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (locked[index] == '0')
                unlockedChars.emplace(index);
            else
            {
                if (s[index] == '(')
                    lockedOpenBraces.emplace(index);
                else
                {
                    if (!lockedOpenBraces.empty())
                        lockedOpenBraces.pop();
                    else if (!unlockedChars.empty())
                        unlockedChars.pop();
                    else
                        return false;
                }
            }
        }
        while (!lockedOpenBraces.empty() && !unlockedChars.empty() && (lockedOpenBraces.top() < unlockedChars.top()))
        {
            lockedOpenBraces.pop();
            unlockedChars.pop();
        }
        return lockedOpenBraces.empty();
    }
};

}

namespace CheckIfParenthesesStringCanBeValidTask
{

TEST(CheckIfParenthesesStringCanBeValidTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canBeValid("))()))", "010100"));
    ASSERT_EQ(true, solution.canBeValid("()()", "0000"));
    ASSERT_EQ(false, solution.canBeValid(")", "0"));
}

}