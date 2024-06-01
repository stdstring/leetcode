#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int scoreOfString(std::string const &s) const
    {
        int result = 0;
        for (size_t index = 1; index < s.size(); ++index)
            result += std::abs(s[index] - s[index - 1]);
        return result;
    }
};

}

namespace ScoreOfStringTask
{

TEST(ScoreOfStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.scoreOfString("hello"));
    ASSERT_EQ(50, solution.scoreOfString("zaz"));
}

}