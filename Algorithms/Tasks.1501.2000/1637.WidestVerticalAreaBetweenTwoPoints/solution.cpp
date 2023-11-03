#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxWidthOfVerticalArea(std::vector<std::vector<int>> const &points) const
    {
        std::vector<int> xCoords(points.size(), 0);
        std::ranges::transform(points, xCoords.begin(), [](std::vector<int> const &point) { return point[0]; });
        std::ranges::sort(xCoords);
        int bestWidth = 0;
        for (size_t index = 1; index < xCoords.size(); ++index)
            bestWidth = std::max(bestWidth, xCoords[index] - xCoords[index - 1]);
        return bestWidth;
    }
};

}

namespace WidestVerticalAreaBetweenTwoPointsTask
{

TEST(WidestVerticalAreaBetweenTwoPointsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.maxWidthOfVerticalArea({{8, 7}, {9, 9}, {7, 4}, {9, 7}}));
    ASSERT_EQ(3, solution.maxWidthOfVerticalArea({{3, 1}, {9, 0}, {1, 0}, {1, 4}, {5, 3}, {8, 8}}));
}

}