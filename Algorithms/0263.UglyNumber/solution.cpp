#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isUgly(int num) const
    {
        if (num <= 0)
            return false;
        while (num % 2 == 0)
            num /= 2;
        while (num % 3 == 0)
            num /= 3;
        while (num % 5 == 0)
            num /= 5;
        return num == 1;
    }
};

}

namespace UglyNumberTask
{

TEST(UglyNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isUgly(6));
    ASSERT_EQ(true, solution.isUgly(8));
    ASSERT_EQ(false, solution.isUgly(14));
}

}