#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int passThePillow(int n, int time) const
    {
        const int passCount = n - 1;
        const int fullPassCount = time / passCount;
        const int passRest = time % passCount;
        return (fullPassCount % 2) == 0 ? 1 + passRest : n - passRest;
    }
};

}

namespace PassPillowTask
{

TEST(PassPillowTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.passThePillow(4, 5));
    ASSERT_EQ(3, solution.passThePillow(3, 2));
}

}