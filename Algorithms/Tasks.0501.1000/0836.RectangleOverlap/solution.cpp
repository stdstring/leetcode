#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isRectangleOverlap(std::vector<int> const &rec1, std::vector<int> const &rec2) const
    {
        // x1, y1 is the coordinate of bottom-left corner
        // x2, y2 is the coordinate of top-right corner
        const int x11 = rec1[0];
        const int y11 = rec1[1];
        const int x12 = rec1[2];
        const int y12 = rec1[3];
        const int x21 = rec2[0];
        const int y21 = rec2[1];
        const int x22 = rec2[2];
        const int y22 = rec2[3];
        if ((x12 <= x21) || (x22 <= x11))
            return false;
        if ((y12 <= y21) || (y22 <= y11))
            return false;
        return true;
    }
};

}

namespace RectangleOverlapTask
{

TEST(RectangleOverlapTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isRectangleOverlap({0, 0, 2, 2}, {1, 1, 3, 3}));
    ASSERT_EQ(false, solution.isRectangleOverlap({0, 0, 1, 1}, {1, 0, 2, 1}));
    ASSERT_EQ(false, solution.isRectangleOverlap({0, 0, 1, 1}, {2, 2, 3, 3}));
}

}