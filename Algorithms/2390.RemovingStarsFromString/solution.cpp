#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string removeStars(std::string const &s) const
    {
        std::string result;
        for (const char ch : s)
        {
            if (ch == '*')
                result.pop_back();
            else
                result.push_back(ch);
        }
        return result;
    }
};

}

namespace RemovingStarsFromStringTask
{

TEST(RemovingStarsFromStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("lecoe", solution.removeStars("leet**cod*e"));
    ASSERT_EQ("", solution.removeStars("erase*****"));
}

}