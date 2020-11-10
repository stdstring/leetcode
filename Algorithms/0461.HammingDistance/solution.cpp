#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int hammingDistance(int x, int y) const
    {
        int distance = 0;
        for (int shift = 0; shift < 31; ++shift)
        {
            const int mask = 1 << shift;
            if (((x ^ y) & mask) != 0)
                ++distance;
        }
        return distance;
    }
};

}

namespace HammingDistanceTask
{

TEST(HammingDistanceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.hammingDistance(1, 4));
}

}