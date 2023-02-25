#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numEnclaves(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<bool> visited(rowCount * columnCount, false);
        size_t cellsCount = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if ((grid[row][column] == 1) && !visited[row * columnCount + column])
                {
                    const std::pair<size_t, bool> result = walkOnLand(grid, visited, row, column);
                    if (!result.second)
                        cellsCount += result.first;
                }
            }
        }
        return static_cast<int>(cellsCount);
    }

private:
    std::pair<size_t, bool> walkOnLand(std::vector<std::vector<int>> const &grid, std::vector<bool> &visited, size_t row, size_t column) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        std::pair<size_t, bool> result(1, (row == 0) || (row == rowMax) || (column == 0) || (column == columnMax));
        visited[row * columnCount + column] = true;
        if ((column > 0) && (grid[row][column - 1] == 1) && !visited[row * columnCount + (column - 1)])
            result = mergeResults(result, walkOnLand(grid, visited, row, column - 1));
        if ((column < columnMax) && (grid[row][column + 1] == 1) && !visited[row * columnCount + (column + 1)])
            result = mergeResults(result, walkOnLand(grid, visited, row, column + 1));
        if ((row > 0) && (grid[row - 1][column] == 1) && !visited[(row - 1) * columnCount + column])
            result = mergeResults(result, walkOnLand(grid, visited, row - 1, column));
        if ((row < rowMax) && (grid[row + 1][column] == 1) && !visited[(row + 1) * columnCount + column])
            result = mergeResults(result, walkOnLand(grid, visited, row + 1, column));
        return result;
    }

    [[nodiscard]] std::pair<size_t, bool> mergeResults(std::pair<size_t, bool> const &result1, std::pair<size_t, bool> const &result2) const
    {
        return {result1.first + result2.first, result1.second | result2.second};
    }
};

}

namespace NumberOfEnclavesTask
{

TEST(NumberOfEnclavesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numEnclaves({{0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}));
    ASSERT_EQ(0, solution.numEnclaves({{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}));
}

TEST(NumberOfEnclavesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numEnclaves({{0, 0, 0, 1, 1, 1, 0, 1, 0, 0},
                                       {1, 1, 0, 0, 0, 1, 0, 1, 1, 1},
                                       {0, 0, 0, 1, 1, 1, 0, 1, 0, 0},
                                       {0, 1, 1, 0, 0, 0, 1, 0, 1, 0},
                                       {0, 1, 1, 1, 1, 1, 0, 0, 1, 0},
                                       {0, 0, 1, 0, 1, 1, 1, 1, 0, 1},
                                       {0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
                                       {0, 0, 1, 0, 0, 1, 0, 1, 0, 1},
                                       {1, 0, 1, 0, 1, 1, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 1, 1, 0, 0, 0, 1}}));
}

}