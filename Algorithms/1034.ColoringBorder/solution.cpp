#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> colorBorder(std::vector<std::vector<int>> const &grid, int row, int col, int color) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<int>> result(grid);
        const int innerColor = grid[row][col];
        std::vector<bool> processed(rowCount * columnCount, false);
        processed[row * columnCount + col] = true;
        if (isBorder(grid, row, col, innerColor))
            result[row][col] = color;
        std::queue<std::pair<size_t, size_t>> queue;
        queue.emplace(row, col);
        while (!queue.empty())
        {
            const auto [currentRow, currentColumn] = queue.front();
            queue.pop();
            if ((currentRow > 0) && !processed[(currentRow - 1) * columnCount + currentColumn] && (grid[currentRow - 1][currentColumn] == innerColor))
                processNextCell(grid, processed, result, queue, currentRow - 1, currentColumn, innerColor, color);
            if ((currentRow < rowMax) && !processed[(currentRow + 1) * columnCount + currentColumn] && (grid[currentRow + 1][currentColumn] == innerColor))
                processNextCell(grid, processed, result, queue, currentRow + 1, currentColumn, innerColor, color);
            if ((currentColumn > 0) && !processed[currentRow * columnCount + currentColumn - 1] && (grid[currentRow][currentColumn - 1] == innerColor))
                processNextCell(grid, processed, result, queue, currentRow, currentColumn - 1, innerColor, color);
            if ((currentColumn < columnMax) && !processed[currentRow * columnCount + currentColumn + 1] && (grid[currentRow][currentColumn + 1] == innerColor))
                processNextCell(grid, processed, result, queue, currentRow, currentColumn + 1, innerColor, color);
        }
        return result;
    }

private:
    [[nodiscard]] bool isBorder(std::vector<std::vector<int>> const &grid, size_t row, size_t column, int innerColor) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        return (row == 0) ||
               (row == rowMax) ||
               (column == 0) ||
               (column == columnMax) ||
               (grid[row][column - 1] != innerColor) ||
               (grid[row][column + 1] != innerColor) ||
               (grid[row - 1][column] != innerColor) ||
               (grid[row + 1][column] != innerColor);
    }

    void processNextCell(std::vector<std::vector<int>> const &grid,
                         std::vector<bool> &processed,
                         std::vector<std::vector<int>> &result,
                         std::queue<std::pair<size_t, size_t>> &queue,
                         size_t row,
                         size_t column,
                         int innerColor,
                         int borderColor) const
    {
        const size_t columnCount = grid.front().size();
        processed[row * columnCount + column] = true;
        if (isBorder(grid, row, column, innerColor))
            result[row][column] = borderColor;
        queue.emplace(row, column);
    }
};

}

namespace ColoringBorderTask
{

TEST(ColoringBorderTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 3}, {3, 2}}), solution.colorBorder({{1, 1}, {1, 2}}, 0, 0, 3));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 3, 3}, {2, 3, 3}}), solution.colorBorder({{1, 2, 2}, {2, 3, 2}}, 0, 1, 3));
    ASSERT_EQ(std::vector<std::vector<int>>({{2, 2, 2}, {2, 1, 2}, {2, 2, 2}}), solution.colorBorder({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, 1, 1, 2));
}

}