#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int getMaximumGold(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<bool> currentPath(rowCount * columnCount, false);
        int maxGold = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] != 0)
                    maxGold = std::max(maxGold, processPath(grid, row, column, currentPath));
            }
        }
        return maxGold;
    }

private:
    [[nodiscard]] int processPath(std::vector<std::vector<int>> const &grid, size_t row, size_t column, std::vector<bool> &currentPath) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        currentPath[row * columnCount + column] = true;
        int maxGold = grid[row][column];
        if ((row > 0) && (grid[row - 1][column] != 0) && !currentPath[(row - 1) * columnCount + column])
            maxGold = std::max(maxGold, grid[row][column] + processPath(grid, row - 1, column, currentPath));
        if ((row < rowMax) && (grid[row + 1][column] != 0) && !currentPath[(row + 1) * columnCount + column])
            maxGold = std::max(maxGold, grid[row][column] + processPath(grid, row + 1, column, currentPath));
        if ((column > 0) && (grid[row][column - 1] != 0) && !currentPath[row * columnCount + column - 1])
            maxGold = std::max(maxGold, grid[row][column] + processPath(grid, row, column - 1, currentPath));
        if ((column < columnMax) && (grid[row][column + 1] != 0) && !currentPath[row * columnCount + column + 1])
            maxGold = std::max(maxGold, grid[row][column] + processPath(grid, row, column + 1, currentPath));
        currentPath[row * columnCount + column] = false;
        return maxGold;
    }
};

}

namespace PathWithMaxGoldTask
{

TEST(PathWithMaxGoldTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(24, solution.getMaximumGold({{0, 6, 0}, {5, 8, 7}, {0, 9, 0}}));
    ASSERT_EQ(28, solution.getMaximumGold({{1, 0, 7}, {2, 0, 6}, {3, 4, 5}, {0, 3, 0}, {9, 0, 20}}));
}

}