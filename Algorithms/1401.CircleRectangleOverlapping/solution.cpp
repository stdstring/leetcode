#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) const
    {
        if ((x1 <= xCenter) && (xCenter <= x2) && (y1 <= yCenter) && (yCenter <= y2))
            return true;
        const int x1DistanceSquare = (y1 <= yCenter) && (yCenter <= y2) ?
                                     (xCenter - x1) * (xCenter - x1) :
                                     calcDistanceSquare(xCenter, yCenter, x1, std::abs(y1 - yCenter) < std::abs(y2 - yCenter) ? y1 : y2);
        const int x2DistanceSquare = (y1 <= yCenter) && (yCenter <= y2) ?
                                     (xCenter - x2) * (xCenter - x2) :
                                     calcDistanceSquare(xCenter, yCenter, x2, std::abs(y1 - yCenter) < std::abs(y2 - yCenter) ? y1 : y2);
        const int y1DistanceSquare = (x1 <= xCenter) && (xCenter <= x2) ?
                                     (yCenter - y1) * (yCenter - y1) :
                                     calcDistanceSquare(xCenter, yCenter, std::abs(x1 - xCenter) < std::abs(x2 - xCenter) ? x1 : x2, y1);
        const int y2DistanceSquare = (x1 <= xCenter) && (xCenter <= x2) ?
                                     (yCenter - y2) * (yCenter - y2) :
                                     calcDistanceSquare(xCenter, yCenter, std::abs(x1 - xCenter) < std::abs(x2 - xCenter) ? x1 : x2, y2);
        const int radiusSquare = radius * radius;
        return std::min(x1DistanceSquare, std::min(x2DistanceSquare, std::min(y1DistanceSquare, y2DistanceSquare))) <= radiusSquare;
    }

private:
    [[nodiscard]] int calcDistanceSquare(int x1, int y1, int x2, int y2) const
    {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }
};

}

namespace CircleRectangleOverlappingTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkOverlap(1, 0, 0, 1, -1, 3, 1));
    ASSERT_EQ(false, solution.checkOverlap(1, 1, 1, 1, -3, 2, -1));
    ASSERT_EQ(true, solution.checkOverlap(1, 0, 0, -1, 0, 0, 1));
}

TEST(TwoSumTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkOverlap(1, 1, 1, -3, -3, 3, 3));
}

}