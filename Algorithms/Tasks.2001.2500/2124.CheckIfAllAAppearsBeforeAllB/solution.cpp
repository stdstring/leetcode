#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkString(std::string const &s) const
    {
        bool hasB = false;
        for (const char ch : s)
        {
            if (ch == 'b')
                hasB = true;
            if ((ch == 'a') && hasB)
                return false;
        }
        return true;
    }
};

}

namespace CheckIfAllAAppearsBeforeAllBTask
{

TEST(CheckIfAllAAppearsBeforeAllBTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkString("aaabbb"));
    ASSERT_EQ(false, solution.checkString("abab"));
    ASSERT_EQ(true, solution.checkString("bbb"));
}

}