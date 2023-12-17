#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimumSteps(std::string const &s) const
    {
        size_t stepCount = 0;
        size_t whiteRight = std::string::npos;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] == '0')
            {
                stepCount += (whiteRight == std::string::npos ? index : index - whiteRight - 1);
                whiteRight = (whiteRight == std::string::npos ? 0 : whiteRight + 1);
            }
        }
        return static_cast<long long>(stepCount);
    }
};

}

namespace SeparateBlackWhiteBallsTask
{

TEST(SeparateBlackWhiteBallsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minimumSteps("101"));
    ASSERT_EQ(2, solution.minimumSteps("100"));
    ASSERT_EQ(0, solution.minimumSteps("0111"));
}

}