#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int shortestBridge(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<bool>> visited(rowCount, std::vector<bool>(columnCount, false));
        // find first island
        auto const &[firstIslandRow, firstIslandColumn] = findIsland(grid);
        // collect first island
        const std::vector<std::pair<size_t, size_t>> islandBorder(collectIsland(grid, firstIslandRow, firstIslandColumn, visited));
        // find shortest path 2 second island
        std::queue<std::pair<size_t, size_t>> queue;
        for (std::pair<size_t, size_t> const &cell : islandBorder)
            queue.emplace(cell);
        int waveFrontDistance = 0;
        while (!queue.empty())
        {
            const size_t queueSize = queue.size();
            for (size_t index = 0; index < queueSize; ++index)
            {
                auto const [row, column] = queue.front();
                queue.pop();
                if ((waveFrontDistance > 0) && (grid[row][column] == 1))
                    return waveFrontDistance - 1;
                if (row > 0)
                    processNextCell(row - 1, column, queue, visited);
                if (row < rowMax)
                    processNextCell(row + 1, column, queue, visited);
                if (column > 0)
                    processNextCell(row, column - 1, queue, visited);
                if (column < columnMax)
                    processNextCell(row, column + 1, queue, visited);
            }
            ++waveFrontDistance;
        }
        return -1;
    }

private:
    [[nodiscard]] std::pair<size_t, size_t> findIsland(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] == 1)
                    return {row, column};
            }
        }
        return {rowCount, columnCount};
    }

    [[nodiscard]] std::vector<std::pair<size_t, size_t>> collectIsland(std::vector<std::vector<int>> const &grid,
                                                                       size_t startRow,
                                                                       size_t startColumn,
                                                                       std::vector<std::vector<bool>> &visited) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        std::vector<std::pair<size_t, size_t>> islandBorder;
        std::queue<std::pair<size_t, size_t>> islandQueue;
        islandQueue.emplace(startRow, startColumn);
        visited[startRow][startColumn] = true;
        while (!islandQueue.empty())
        {
            auto const [row, column] = islandQueue.front();
            islandQueue.pop();
            if (isBorder(grid, row, column))
                islandBorder.emplace_back(row, column);
            if ((row > 0) && (grid[row - 1][column] == 1))
                processNextCell(row - 1, column, islandQueue, visited);
            if ((row < rowMax) && (grid[row + 1][column] == 1))
                processNextCell(row + 1, column, islandQueue, visited);
            if ((column > 0) && (grid[row][column - 1] == 1))
                processNextCell(row, column - 1, islandQueue, visited);
            if ((column < columnMax) && (grid[row][column + 1] == 1))
                processNextCell(row, column + 1, islandQueue, visited);
        }
        return islandBorder;
    }

    [[nodiscard]] bool isBorder(std::vector<std::vector<int>> const &grid, size_t row, size_t column) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        if (grid[row][column] != 1)
            return false;
        return ((row > 0) && (grid[row - 1][column] == 0)) ||
               ((row < rowMax) && (grid[row + 1][column] == 0)) ||
               ((column > 0) && (grid[row][column - 1] == 0)) ||
               ((column < columnMax) && (grid[row][column + 1] == 0));
    }

    void processNextCell(size_t row, size_t column, std::queue<std::pair<size_t, size_t>> &queue, std::vector<std::vector<bool>> &visited) const
    {
        if (!visited[row][column])
        {
            visited[row][column] = true;
            queue.emplace(row, column);
        }
    }
};

}

namespace ShortestBridgeTask
{

TEST(ShortestBridgeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.shortestBridge({{0, 1}, {1, 0}}));
    ASSERT_EQ(2, solution.shortestBridge({{0, 1, 0}, {0, 0, 0}, {0, 0, 1}}));
    ASSERT_EQ(1, solution.shortestBridge({{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}}));
}

TEST(ShortestBridgeTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.shortestBridge({{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                          {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
                                          {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                                          {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                                          {1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
                                          {1, 1, 0, 1, 1, 1, 1, 1, 1, 1}}));
}

}