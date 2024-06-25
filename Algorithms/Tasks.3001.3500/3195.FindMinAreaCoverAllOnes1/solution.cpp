#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumArea(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        size_t minRow = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            minRow = row;
            if (hasOneInRow(grid, row))
                break;
        }
        size_t maxRow = rowCount - 1;
        for (size_t row = rowCount - 1; row >= minRow; --row)
        {
            maxRow = row;
            if (hasOneInRow(grid, row))
                break;
        }
        size_t minColumn = 0;
        for (size_t column = 0; column < columnCount; ++column)
        {
            minColumn = column;
            if (hasOneInColumn(grid, column))
                break;
        }
        size_t maxColumn = columnCount - 1;
        for (size_t column = columnCount - 1; column >= minColumn; --column)
        {
            maxColumn = column;
            if (hasOneInColumn(grid, column))
                break;
        }
        return static_cast<int>((maxRow - minRow + 1) * (maxColumn - minColumn + 1));
    }

private:
    [[nodiscard]] bool hasOneInRow(std::vector<std::vector<int>> const &grid, size_t row) const
    {
        const size_t columnCount = grid.front().size();
        for (size_t column = 0; column < columnCount; ++column)
        {
            if (grid[row][column] == 1)
                return true;
        }
        return false;
    }

    [[nodiscard]] bool hasOneInColumn(std::vector<std::vector<int>> const &grid, size_t column) const
    {
        const size_t rowCount = grid.size();
        for (size_t row = 0; row < rowCount; ++row)
        {
            if (grid[row][column] == 1)
                return true;
        }
        return false;
    }
};

}

namespace FindMinAreaCoverAllOnes1Task
{

TEST(FindMinAreaCoverAllOnes1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.minimumArea({{0, 1, 0}, {1, 0, 1}}));
    ASSERT_EQ(1, solution.minimumArea({{1, 0}, {0, 0}}));
}

}