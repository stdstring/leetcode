#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxAreaOfIsland(std::vector<std::vector<int>> const &grid) const
    {
        std::vector<std::vector<int>> buffer(grid);
        int maxArea = 0;
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (buffer[row][column] != 0)
                {
                    int area = processIsland(buffer, row, column);
                    maxArea = std::max(area, maxArea);
                }
            }
        }
        return maxArea;
    }

private:
    int processIsland(std::vector<std::vector<int>> &buffer, size_t row, size_t column) const
    {
        int area = 1;
        buffer[row][column] = 0;
        const size_t rowMax = buffer.size() - 1;
        const size_t columnMax = buffer.front().size() - 1;
        if ((row > 0) && (buffer[row - 1][column] == 1))
            area += processIsland(buffer, row - 1, column);
        if ((row < rowMax) && (buffer[row + 1][column] == 1))
            area += processIsland(buffer, row + 1, column);
        if ((column > 0) && (buffer[row][column - 1] == 1))
            area += processIsland(buffer, row, column - 1);
        if ((column < columnMax) && (buffer[row][column + 1] == 1))
            area += processIsland(buffer, row, column + 1);
        return area;
    }
};

}

namespace MaxAreaOfIslandTask
{

TEST(MaxAreaOfIslandTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.maxAreaOfIsland({{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                           {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                                           {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                           {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}}));
    ASSERT_EQ(0, solution.maxAreaOfIsland({{0, 0, 0, 0, 0, 0, 0, 0}}));
}

}