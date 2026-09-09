#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countCommas(int n) const
    {
        int result = 0;
        if (n > 999)
            result += (n - 999);
        if (n > 999999)
            result += (n - 999999);
        if (n > 999999999)
            result += (n - 999999999);
        return result;
    }
};

}

namespace CountCommasInRange1Task
{

TEST(CountCommasInRange1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countCommas(1002));
    ASSERT_EQ(0, solution.countCommas(998));
}

}