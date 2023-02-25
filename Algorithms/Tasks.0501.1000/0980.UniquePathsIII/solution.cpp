#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int uniquePathsIII(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const int totalMask = (1 << (rowCount * columnCount)) - 1;
        int currentMask = 0;
        size_t startRow = 0;
        size_t startColumn = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] == NonEmptyCell)
                    currentMask |= (1 << (row * columnCount + column));
                if (grid[row][column] == StartCell)
                {
                    startRow = row;
                    startColumn = column;
                    currentMask |= (1 << (row * columnCount + column));
                }
            }
        }
        return static_cast<int>(calcUniquePaths(grid, currentMask, totalMask, startRow, startColumn));
    }

private:
    static constexpr int StartCell = 1;
    static constexpr int FinishCell = 2;
    static constexpr int NonEmptyCell = -1;

    [[nodiscard]] size_t calcUniquePaths(std::vector<std::vector<int>> const &grid, int currentMask, int totalMask, size_t row, size_t column) const
    {
        if (grid[row][column] == FinishCell)
            return currentMask == totalMask ? 1 : 0;
        size_t uniquePathCount = 0;
        const size_t rowMax = grid.size() - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        if (row > 0)
        {
            const int mask = 1 << ((row - 1) * columnCount + column);
            if ((mask & currentMask) == 0)
                uniquePathCount += calcUniquePaths(grid, currentMask | mask, totalMask, row - 1, column);
        }
        if (row < rowMax)
        {
            const int mask = 1 << ((row + 1) * columnCount + column);
            if ((mask & currentMask) == 0)
                uniquePathCount += calcUniquePaths(grid, currentMask | mask, totalMask, row + 1, column);
        }
        if (column > 0)
        {
            const int mask = 1 << (row * columnCount + column - 1);
            if ((mask & currentMask) == 0)
                uniquePathCount += calcUniquePaths(grid, currentMask | mask, totalMask, row, column - 1);
        }
        if (column < columnMax)
        {
            const int mask = 1 << (row * columnCount + column + 1);
            if ((mask & currentMask) == 0)
                uniquePathCount += calcUniquePaths(grid, currentMask | mask, totalMask, row, column + 1);
        }
        return uniquePathCount;
    }
};

}

namespace UniquePathsIIITask
{

TEST(UniquePathsIIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.uniquePathsIII({{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}}));
    ASSERT_EQ(4, solution.uniquePathsIII({{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 2}}));
    ASSERT_EQ(0, solution.uniquePathsIII({{0, 1}, {2, 0}}));
}

}