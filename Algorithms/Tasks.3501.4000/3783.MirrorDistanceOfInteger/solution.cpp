#include <cmath>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int mirrorDistance(int n) const
    {
        return std::abs(n - reverse(n));
    }

private:
    [[nodiscard]] int reverse(int number) const
    {
        int result = 0;
        for (; number > 0; number /= 10)
            result = 10 * result + (number % 10);
        return result;
    }
};

}

namespace MirrorDistanceOfIntegerTask
{

TEST(MirrorDistanceOfIntegerTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(27, solution.mirrorDistance(25));
    ASSERT_EQ(9, solution.mirrorDistance(10));
    ASSERT_EQ(0, solution.mirrorDistance(7));
}

}