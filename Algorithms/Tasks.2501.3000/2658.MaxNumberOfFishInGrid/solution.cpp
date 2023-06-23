#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findMaxFish(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<bool>> visited(rowCount, std::vector<bool>(columnCount, false));
        int result = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if ((grid[row][column] > 0) && !visited[row][column])
                    result = std::max(result, collectFish(grid, row, column, visited));
            }
        }
        return result;
    }

private:
    [[nodiscard]] int collectFish(std::vector<std::vector<int>> const &grid, size_t startRow, size_t startColumn, std::vector<std::vector<bool>> &visited) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        int result = 0;
        visited[startRow][startColumn] = true;
        std::queue<std::pair<size_t, size_t>> queue;
        queue.emplace(startRow, startColumn);
        while (!queue.empty())
        {
            auto [row, column] = queue.front();
            queue.pop();
            result += grid[row][column];
            if ((row > 0) && (grid[row - 1][column] > 0) && !visited[row - 1][column])
            {
                visited[row - 1][column] = true;
                queue.emplace(row - 1, column);
            }
            if ((row < rowMax) && (grid[row + 1][column] > 0) && !visited[row + 1][column])
            {
                visited[row + 1][column] = true;
                queue.emplace(row + 1, column);
            }
            if ((column > 0) && (grid[row][column - 1] > 0) && !visited[row][column - 1])
            {
                visited[row][column - 1] = true;
                queue.emplace(row, column - 1);
            }
            if ((column < columnMax) && (grid[row][column + 1] > 0) && !visited[row][column + 1])
            {
                visited[row][column + 1] = true;
                queue.emplace(row, column + 1);
            }
        }
        return result;
    }
};

}

namespace MaxNumberOfFishInGridTask
{

TEST(MaxNumberOfFishInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.findMaxFish({{0, 2, 1, 0}, {4, 0, 0, 3}, {1, 0, 0, 4}, {0, 3, 2, 0}}));
    ASSERT_EQ(1, solution.findMaxFish({{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}}));
}

}