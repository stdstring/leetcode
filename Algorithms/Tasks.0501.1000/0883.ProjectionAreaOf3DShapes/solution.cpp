#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int projectionArea(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        int xyProjection = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] > 0)
                    ++xyProjection;
            }
        }
        int xzProjection = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            xzProjection += (*std::max_element(grid[row].cbegin(), grid[row].cend()));
        }
        int yzProjection = 0;
        for (size_t column = 0; column < columnCount; ++column)
        {
            int maxValue = 0;
            for (size_t row = 0; row < rowCount; ++row)
                maxValue = std::max(maxValue, grid[row][column]);
            yzProjection += maxValue;
        }
        return xyProjection + xzProjection + yzProjection;
    }
};

}

namespace ProjectionAreaOf3DShapesTask
{

TEST(ProjectionAreaOf3DShapesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(17, solution.projectionArea({{1, 2}, {3, 4}}));
    ASSERT_EQ(5, solution.projectionArea({{2}}));
    ASSERT_EQ(8, solution.projectionArea({{1, 0}, {0, 2}}));
    ASSERT_EQ(14, solution.projectionArea({{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}));
    ASSERT_EQ(21, solution.projectionArea({{2, 2, 2}, {2, 1, 2}, {2, 2, 2}}));
}

}