#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int nearestValidPoint(int x, int y, std::vector<std::vector<int>> const &points) const
    {
        int nearestPointIndex = -1;
        int nearestPointDist = -1;
        for (size_t index = 0; index < points.size(); ++index)
        {
            if ((points[index][0] != x) && (points[index][1] != y))
                continue;
            const int pointDist = std::abs(points[index][0] - x) + std::abs(points[index][1] - y);
            if ((nearestPointIndex == -1) || (pointDist < nearestPointDist))
            {
                nearestPointIndex = static_cast<int>(index);
                nearestPointDist = pointDist;
            }
        }
        return nearestPointIndex;
    }
};

}

namespace FindNearestPointThatHasSameXOrYCoordTask
{

TEST(FindNearestPointThatHasSameXOrYCoordTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.nearestValidPoint(3, 4, {{1, 2}, {3, 1}, {2, 4}, {2, 3}, {4, 4}}));
    ASSERT_EQ(0, solution.nearestValidPoint(3, 4, {{3, 4}}));
    ASSERT_EQ(-1, solution.nearestValidPoint(3, 4, {{2, 3}}));
}

}