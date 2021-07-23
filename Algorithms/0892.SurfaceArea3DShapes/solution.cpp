#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int surfaceArea(std::vector<std::vector<int>> const &grid) const
    {
        int area = 0;
        for (size_t row = 0; row < grid.size(); ++row)
        {
            for (size_t column = 0; column < grid[row].size(); ++column)
            {
                const int height = grid[row][column];
                const int topHeight = row == 0 ? 0 : grid[row - 1][column];
                const int leftHeight = column == 0 ? 0 : grid[row][column - 1];
                const int bottomHeight = row == grid.size() - 1 ? 0 : grid[row + 1][column];
                const int rightHeight = column == grid[row].size() - 1 ? 0 : grid[row][column + 1];
                if (height == 0)
                    continue;
                area += 2;
                if (height > topHeight)
                    area += (height - topHeight);
                if (height > leftHeight)
                    area += (height - leftHeight);
                if (height > bottomHeight)
                    area += (height - bottomHeight);
                if (height > rightHeight)
                    area += (height - rightHeight);
            }
        }
        return area;
    }
};

}

namespace SurfaceArea3DShapesTask
{

TEST(SurfaceArea3DShapesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(10, solution.surfaceArea({{2}}));
    ASSERT_EQ(34, solution.surfaceArea({{1, 2}, {3, 4}}));
    ASSERT_EQ(16, solution.surfaceArea({{1, 0}, {0, 2}}));
    ASSERT_EQ(32, solution.surfaceArea({{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}));
    ASSERT_EQ(46, solution.surfaceArea({{2, 2, 2}, {2, 1, 2}, {2, 2, 2}}));
}

}