#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDepth(std::string const &s) const
    {
        int result = 0;
        int currentDepth = 0;
        for (const char ch : s)
        {
            switch (ch)
            {
            case '(':
                ++currentDepth;
                break;
            case ')':
                --currentDepth;
                break;
            default:
                break;
            }
            result = std::max(result, currentDepth);
        }
        return result;
    }
};

}

namespace MaxNestingDepthOfParenthesesTask
{

TEST(MaxNestingDepthOfParenthesesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxDepth("(1+(2*3)+((8)/4))+1"));
    ASSERT_EQ(3, solution.maxDepth("(1)+((2))+(((3)))"));
}

}