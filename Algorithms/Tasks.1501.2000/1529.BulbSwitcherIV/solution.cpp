#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minFlips(std::string const &target) const
    {
        size_t minFlipCount = 0;
        for (size_t index = 0; index < target.size(); ++index)
        {
            const char prevChar = index > 0 ? target[index - 1] : '0';
            if (target[index] != prevChar)
                ++minFlipCount;
        }
        return static_cast<int>(minFlipCount);
    }
};

}

namespace BulbSwitcherIVTask
{

TEST(BulbSwitcherIVTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.minFlips("10111"));
    ASSERT_EQ(3, solution.minFlips("101"));
    ASSERT_EQ(0, solution.minFlips("00000"));
    ASSERT_EQ(5, solution.minFlips("001011101"));
}

TEST(BulbSwitcherIVTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.minFlips("11000"));
}

}