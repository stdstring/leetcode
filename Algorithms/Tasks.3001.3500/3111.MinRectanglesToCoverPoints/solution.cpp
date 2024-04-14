#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minRectanglesToCoverPoints(std::vector<std::vector<int>> const &points, int w) const
    {
        std::vector<int> xCoords;
        xCoords.reserve(points.size());
        for (std::vector<int> const& point : points)
            xCoords.emplace_back(point[0]);
        std::ranges::sort(xCoords);
        int start = xCoords.front();
        size_t rectangleCount = 1;
        for (int xCoord : xCoords)
        {
            if (xCoord > (start + w))
            {
                start = xCoord;
                ++rectangleCount;
            }
        }
        return static_cast<int>(rectangleCount);
    }
};

}

namespace MinRectanglesToCoverPointsTask
{

TEST(MinRectanglesToCoverPointsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minRectanglesToCoverPoints({{2, 1}, {1, 0}, {1, 4}, {1, 8}, {3, 5}, {4, 6}}, 1));
    ASSERT_EQ(3, solution.minRectanglesToCoverPoints({{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}}, 2));
    ASSERT_EQ(2, solution.minRectanglesToCoverPoints({{2, 3}, {1, 2}}, 0));
}

}