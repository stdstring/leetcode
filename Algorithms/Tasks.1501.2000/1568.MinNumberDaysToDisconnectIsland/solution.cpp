#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minDays(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<bool>> visited(rowCount, std::vector<bool>(columnCount, false));
        std::vector<std::pair<size_t, size_t>> island;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (visited[row][column])
                    continue;
                visited[row][column] = true;
                if (grid[row][column] == 1)
                {
                    if (!island.empty())
                        return 0;
                    island = findIsland(grid, row, column, visited);
                }
            }
        }
        switch (island.size())
        {
            case 0:
                return 0;
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return 1;
        default:
                return hasCellWhichDivideIslandOn2Part(grid, island) ? 1 : 2;
        }
    }

private:
    [[nodiscard]] std::vector<std::pair<size_t, size_t>> findIsland(std::vector<std::vector<int>> const &grid,
                                                                    size_t startRow,
                                                                    size_t startColumn,
                                                                    std::vector<std::vector<bool>> &visited) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::queue<std::pair<size_t, size_t>> islandQueue;
        std::vector<std::pair<size_t, size_t>> island;
        island.reserve(rowCount * columnCount);
        islandQueue.emplace(startRow, startColumn);
        while (!islandQueue.empty())
        {
            auto [row, column] = islandQueue.front();
            islandQueue.pop();
            island.emplace_back(row, column);
            if ((row > 0) && (grid[row - 1][column] == 1) && !visited[row - 1][column])
            {
                visited[row - 1][column] = true;
                islandQueue.emplace(row - 1, column);
            }
            if ((row < (rowCount - 1)) && (grid[row + 1][column] == 1) && !visited[row + 1][column])
            {
                visited[row + 1][column] = true;
                islandQueue.emplace(row + 1, column);
            }
            if ((column > 0) && (grid[row][column - 1] == 1) && !visited[row][column - 1])
            {
                visited[row][column - 1] = true;
                islandQueue.emplace(row, column - 1);
            }
            if ((column < (columnCount - 1)) && (grid[row][column + 1] == 1) && !visited[row][column + 1])
            {
                visited[row][column + 1] = true;
                islandQueue.emplace(row, column + 1);
            }
        }
        return island;
    }

    [[nodiscard]] bool hasCellWhichDivideIslandOn2Part(std::vector<std::vector<int>> const &grid,
                                                       std::vector<std::pair<size_t, size_t>> const &island) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        for (size_t deletedIndex = 0; deletedIndex < island.size(); ++deletedIndex)
        {
            auto [deletedRow, deletedColumn] = island[deletedIndex];
            std::vector<std::vector<bool>> visited(rowCount, std::vector<bool>(columnCount, false));
            size_t visitedCount = 0;
            std::queue<std::pair<size_t, size_t>> islandQueue;
            const size_t firstIndex = deletedIndex == 0 ? 1 : 0;
            islandQueue.emplace(island[firstIndex]);
            visited[island[firstIndex].first][island[firstIndex].second] = true;
            while (!islandQueue.empty())
            {
                auto [row, column] = islandQueue.front();
                islandQueue.pop();
                if ((row  == deletedRow) && (column == deletedColumn))
                    continue;
                ++visitedCount;
                if ((row > 0) && (grid[row - 1][column] == 1) && !visited[row - 1][column])
                {
                    visited[row - 1][column] = true;
                    islandQueue.emplace(row - 1, column);
                }
                if ((row < (rowCount - 1)) && (grid[row + 1][column] == 1) && !visited[row + 1][column])
                {
                    visited[row + 1][column] = true;
                    islandQueue.emplace(row + 1, column);
                }
                if ((column > 0) && (grid[row][column - 1] == 1) && !visited[row][column - 1])
                {
                    visited[row][column - 1] = true;
                    islandQueue.emplace(row, column - 1);
                }
                if ((column < (columnCount - 1)) && (grid[row][column + 1] == 1) && !visited[row][column + 1])
                {
                    visited[row][column + 1] = true;
                    islandQueue.emplace(row, column + 1);
                }
            }
            if (visitedCount < (island.size() - 1))
                return true;
        }
        return false;
    }
};

}

namespace MinNumberDaysToDisconnectIslandTask
{

TEST(MinNumberDaysToDisconnectIslandTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minDays({{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}));
    ASSERT_EQ(2, solution.minDays({{1, 1}}));
}

TEST(MinNumberDaysToDisconnectIslandTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minDays({{1, 1, 0, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 0, 1, 1}, {1, 1, 0, 1, 1}}));
    ASSERT_EQ(2, solution.minDays({{1, 1, 0, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 0, 1, 1}, {1, 1, 1, 1, 1}}));
    ASSERT_EQ(1, solution.minDays({{1, 1, 1, 1, 0, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {0, 1, 1, 1, 0, 1},
                                   {1, 1, 0, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1},
                                   {0, 1, 1, 0, 1, 1}}));
}

}