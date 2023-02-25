#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string makeGood(std::string const &s) const
    {
        std::string result;
        for (const char ch : s)
        {
            if (!result.empty() && (ch != result.back()) && (std::tolower(ch) == std::tolower(result.back())))
                result.pop_back();
            else
                result.push_back(ch);
        }
        return result;
    }
};

}

namespace MakeStringGreatTask
{

TEST(MakeStringGreatTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("leetcode", solution.makeGood("leEeetcode"));
    ASSERT_EQ("", solution.makeGood("abBAcC"));
    ASSERT_EQ("s", solution.makeGood("s"));
}

}