#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countCommas(long long n) const
    {
        long long result = 0;
        if (n > 999ll)
            result += (n - 999ll);
        if (n > 999999ll)
            result += (n - 999999ll);
        if (n > 999999999ll)
            result += (n - 999999999ll);
        if (n > 999999999999ll)
            result += (n - 999999999999ll);
        if (n > 999999999999999ll)
            result += (n - 999999999999999ll);
        return result;
    }
};

}

namespace CountCommasInRange2Task
{

TEST(CountCommasInRange2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countCommas(1002));
    ASSERT_EQ(0, solution.countCommas(998));
}

}