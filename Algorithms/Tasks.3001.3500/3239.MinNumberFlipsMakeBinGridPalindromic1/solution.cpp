#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minFlips(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        size_t rowsFlipCount = 0;
        for (size_t row = 0; row < rowCount; ++row)
            rowsFlipCount += flipForRow(grid, row);
        size_t columnsFlipCount = 0;
        for (size_t column = 0; column < columnCount; ++column)
            columnsFlipCount += flipForColumn(grid, column);
        return static_cast<int>(std::min(rowsFlipCount, columnsFlipCount));
    }

private:
    [[nodiscard]] size_t flipForRow(std::vector<std::vector<int>> const &grid, size_t row) const
    {
        const size_t columnCount = grid.front().size();
        size_t flipCount = 0;
        for (size_t start = 0, end = columnCount - 1; start < end; ++start, --end)
        {
            if (grid[row][start] != grid[row][end])
                ++flipCount;
        }
        return flipCount;
    }

    [[nodiscard]] size_t flipForColumn(std::vector<std::vector<int>> const &grid, size_t column) const
    {
        const size_t rowCount = grid.size();
        size_t flipCount = 0;
        for (size_t start = 0, end = rowCount - 1; start < end; ++start, --end)
        {
            if (grid[start][column] != grid[end][column])
                ++flipCount;
        }
        return flipCount;
    }
};

}

namespace MinNumberFlipsMakeBinGridPalindromic1Task
{

TEST(MinNumberFlipsMakeBinGridPalindromic1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minFlips({{1, 0, 0}, {0, 0, 0}, {0, 0, 1}}));
    ASSERT_EQ(1, solution.minFlips({{0, 1}, {0, 1}, {0, 0}}));
    ASSERT_EQ(0, solution.minFlips({{1}, {0}}));
}

}