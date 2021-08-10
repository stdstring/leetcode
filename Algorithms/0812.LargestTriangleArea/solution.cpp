#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    double largestTriangleArea(std::vector<std::vector<int>> const &points) const
    {
        int largestArea = 0;
        for (size_t first = 0; first < points.size() - 2; ++first)
        {
            for (size_t second = 0; second < points.size() - 1; ++second)
            {
                const int vectorAX = points[second][0] - points[first][0];
                const int vectorAY = points[second][1] - points[first][1];
                for (size_t third = 0; third < points.size(); ++third)
                {
                    const int vectorBX = points[third][0] - points[first][0];
                    const int vectorBY = points[third][1] - points[first][1];
                    // cross product
                    int currentArea = std::abs(vectorAX * vectorBY - vectorAY * vectorBX);
                    largestArea = std::max(largestArea, currentArea);
                }
            }
        }
        return static_cast<double>(largestArea) / 2;
    }
};

}

namespace LargestTriangleAreaTask
{

TEST(LargestTriangleAreaTaskTests, Examples)
{
    const Solution solution;
    ASSERT_DOUBLE_EQ(2.0, solution.largestTriangleArea({{0, 0}, {0, 1}, {1, 0}, {0, 2}, {2, 0}}));
    ASSERT_DOUBLE_EQ(0.5, solution.largestTriangleArea({{1, 0}, {0, 0}, {0, 1}}));
}

}