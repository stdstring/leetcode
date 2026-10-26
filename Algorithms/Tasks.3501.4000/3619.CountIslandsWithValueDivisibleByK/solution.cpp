#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countIslands(std::vector<std::vector<int>> const &grid, int k) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        size_t result = 0;
        std::vector<std::vector<bool>> visited(rowCount, std::vector<bool>(columnCount, false));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if ((grid[row][column] != 0) && !visited[row][column])
                {
                    const int islandValue = processIsland(row, column, grid, visited, k);
                    if (islandValue == 0)
                        ++result;
                }
            }
        }
        return static_cast<int>(result);
    }

private:
    [[nodiscard]] int processIsland(size_t row, size_t column, std::vector<std::vector<int>> const &grid, std::vector<std::vector<bool>> &visited, int k) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        visited[row][column] = true;
        int result = grid[row][column] % k;
        if ((row > 0) && (grid[row - 1][column] != 0) && !visited[row - 1][column])
            result = (result + processIsland(row - 1, column, grid, visited, k)) % k;
        if ((row < rowMax) && (grid[row + 1][column] != 0) && !visited[row + 1][column])
            result = (result + processIsland(row + 1, column, grid, visited, k)) % k;
        if ((column > 0) && (grid[row][column - 1] != 0) && !visited[row][column - 1])
            result = (result + processIsland(row, column - 1, grid, visited, k)) % k;
        if ((column < columnMax) && (grid[row][column + 1] != 0) && !visited[row][column + 1])
            result = (result + processIsland(row, column + 1, grid, visited, k)) % k;
        return result;
    }
};

}

namespace CountIslandsWithValueDivisibleByKTask
{

TEST(CountIslandsWithValueDivisibleByKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countIslands({{0, 2, 1, 0, 0}, {0, 5, 0, 0, 5}, {0, 0, 1, 0, 0}, {0, 1, 4, 7, 0}, {0, 2, 0, 0, 8}}, 5));
    ASSERT_EQ(6, solution.countIslands({{3, 0, 3, 0}, {0, 3, 0, 3}, {3, 0, 3, 0}}, 3));
}

}
