#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool canWinNim(int n) const
    {
        return (n % 4) > 0;
    }
};

}

namespace NimGameTask
{

TEST(NimGameTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.canWinNim(4));
}

}