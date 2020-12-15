#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numIslands(std::vector<std::vector<char>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<uint8_t>> data(rowCount, std::vector<uint8_t>(columnCount, 0));
        size_t islandsCount = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] == '1' && data[row][column] == 0)
                {
                    processIsland(grid, data, row, column);
                    ++islandsCount;
                }
            }
        }
        return static_cast<int>(islandsCount);
    }

private:
    void processIsland(std::vector<std::vector<char>> const &grid, std::vector<std::vector<uint8_t>> &data, size_t row, size_t column) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        data[row][column] = 1;
        if (row > 0 && grid[row - 1][column] == '1' && data[row - 1][column] == 0)
            processIsland(grid, data, row - 1, column);
        if (row < rowMax && grid[row + 1][column] == '1' && data[row + 1][column] == 0)
            processIsland(grid, data, row + 1, column);
        if (column > 0 && grid[row][column - 1] == '1' && data[row][column - 1] == 0)
            processIsland(grid, data, row, column - 1);
        if (column < columnMax && grid[row][column + 1] == '1' && data[row][column + 1] == 0)
            processIsland(grid, data, row, column + 1);
    }
};

}

namespace NumberOfIslandsTask
{

TEST(NumberOfIslandsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.numIslands({{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}}));
    ASSERT_EQ(3, solution.numIslands({{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}}));
}

}