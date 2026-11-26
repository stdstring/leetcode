#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canAliceWin(int n) const
    {
        int step = 1;
        int currentRemove = 10;
        while (n >= currentRemove)
        {
            n -= currentRemove;
            --currentRemove;
            ++step;
        }
        return (step % 2) == 0;
    }
};

}

namespace StoneRemovalGameTask
{

TEST(StoneRemovalGameTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canAliceWin(12));
    ASSERT_EQ(false, solution.canAliceWin(1));
}

}