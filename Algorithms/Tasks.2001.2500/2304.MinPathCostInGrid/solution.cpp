#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minPathCost(std::vector<std::vector<int>> const &grid, std::vector<std::vector<int>> const &moveCost) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<int> currentRow(grid.front());
        std::vector<int> nextRow(columnCount, INT_MAX);
        for (size_t row = 0; row < rowCount - 1; ++row)
        {
            for (size_t fromColumn = 0; fromColumn < columnCount; ++fromColumn)
            {
                const int fromCellValue = grid[row][fromColumn];
                for (size_t toColumn = 0; toColumn < columnCount; ++toColumn)
                {
                    const int toCellValue = grid[row + 1][toColumn];
                    const int moveValue = moveCost[fromCellValue][toColumn];
                    nextRow[toColumn] = std::min(nextRow[toColumn], currentRow[fromColumn] + moveValue + toCellValue);
                }
            }
            std::swap(currentRow, nextRow);
            for (size_t column = 0; column < columnCount; ++column)
                nextRow[column] = INT_MAX;
        }
        return std::ranges::min(currentRow);
    }
};

}

namespace MinPathCostInGridTask
{

TEST(MinPathCostInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(17, solution.minPathCost({{5, 3}, {4, 0}, {2, 1}}, {{9, 8}, {1, 5}, {10, 12}, {18, 6}, {2, 4}, {14, 3}}));
    ASSERT_EQ(6, solution.minPathCost({{5, 1, 2}, {4, 0, 3}}, {{12, 10, 15}, {20, 23, 8}, {21, 7, 1}, {8, 1, 13}, {9, 10, 25}, {5, 3, 2}}));
}

}