#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int bulbSwitch(int n) const
    {
        // Description : anyone can see, that only bulbs with numbers with numbers like 2^(2 * p2) * 3^(2 * p3) * 5^(2 * p5) ... are turning on
        size_t count = 0;
        int number = 1;
        while (number * number <= n)
        {
            ++count;
            ++number;
        }
        return static_cast<int>(count);
    }
};

}

namespace BulbSwitcherTask
{

TEST(BulbSwitcherTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.bulbSwitch(3));
    ASSERT_EQ(0, solution.bulbSwitch(0));
    ASSERT_EQ(1, solution.bulbSwitch(1));
}

}