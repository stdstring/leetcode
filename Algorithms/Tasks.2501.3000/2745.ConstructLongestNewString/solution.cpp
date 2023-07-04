#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestString(int x, int y, int z) const
    {
        // x - "AA", y - "BB", z - "AB"
        return 2 * (2 * std::min(x, y) + (x == y ? 0 : 1) + z);
    }
};

}

namespace ConstructLongestNewStringTask
{

TEST(ConstructLongestNewStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.longestString(2, 5, 1));
    ASSERT_EQ(14, solution.longestString(3, 2, 2));
}

}