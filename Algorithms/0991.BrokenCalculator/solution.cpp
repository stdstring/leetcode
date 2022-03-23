#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int brokenCalc(int x, int y) const
    {
        if (x >= y)
            return x - y;
        size_t count = 0;
        while (x < y)
        {
            // The motivation for this is that it turns out we always greedily divide by 2:
            // 1) If say target is even, then if we perform 2 additions and one division,
            //    we could instead perform one division and one addition for less operations [(target + 2) / 2 vs target / 2 + 1].
            // 2) If say target is odd, then if we perform 3 additions and one division,
            //    we could instead perform 1 addition, 1 division, and 1 addition for less operations [(target + 3) / 2 vs(target + 1) / 2 + 1].
            ++count;
            y = (y % 2 == 1 ? y + 1 : y / 2);
        }
        return static_cast<int>(count) + (x - y);
    }
};

}

namespace BrokenCalculatorTask
{

TEST(BrokenCalculatorTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.brokenCalc(2, 3));
    ASSERT_EQ(2, solution.brokenCalc(5, 8));
    ASSERT_EQ(3, solution.brokenCalc(3, 10));
}

}