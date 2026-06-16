#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string processStr(std::string const &s) const
    {
        std::string result;
        for (const char ch : s)
        {
            switch (ch)
            {
                case '*':
                    if (!result.empty())
                        result.pop_back();
                    break;
                case '#':
                    result += result;
                    break;
                case '%':
                    std::ranges::reverse(result);
                    break;
                default:
                    result.push_back(ch);
            }
        }
        return result;
    }
};

}

namespace ProcessStringWithSpecialOps1Task
{

TEST(ProcessStringWithSpecialOps1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("ba", solution.processStr("a#b%*"));
    ASSERT_EQ("", solution.processStr("z*#"));
}

}