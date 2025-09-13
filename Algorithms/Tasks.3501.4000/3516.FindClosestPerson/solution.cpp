#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findClosest(int x, int y, int z) const
    {
        const int distanceXZ = std::abs(x - z);
        const int distanceYZ = std::abs(y - z);
        if (distanceXZ < distanceYZ)
            return 1;
        if (distanceYZ < distanceXZ)
            return 2;
        return 0;
    }
};

}

namespace FindClosestPersonTask
{

TEST(FindClosestPersonTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.findClosest(2, 7, 4));
    ASSERT_EQ(2, solution.findClosest(2, 5, 6));
    ASSERT_EQ(0, solution.findClosest(1, 5, 3));
}

}