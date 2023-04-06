#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int closedIsland(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<bool>> visited(rowCount, std::vector<bool>(columnCount, false));
        size_t closedIslandCount = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if ((grid[row][column] == LandValue) && (!visited[row][column]))
                {
                    if (processIsland(grid, visited, row, column))
                        ++closedIslandCount;
                }
            }
        }
        return static_cast<int>(closedIslandCount);
    }

private:
    static constexpr int LandValue = 0;

    [[nodiscard]] bool processIsland(std::vector<std::vector<int>> const &grid, std::vector<std::vector<bool>> &visited, size_t startRow, size_t startColumn) const
    {
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        bool isClosed = true;
        std::queue<std::pair<size_t, size_t>> queue;
        queue.emplace(startRow, startColumn);
        while (!queue.empty())
        {
            auto [row, column] = queue.front();
            queue.pop();
            isClosed &= ((row > 0) && (row < rowMax) && (column > 0) && (column < columnMax));
            if (row > 0)
                processCell(grid, visited, queue, row - 1, column);
            if (row < rowMax)
                processCell(grid, visited, queue, row + 1, column);
            if (column > 0)
                processCell(grid, visited, queue, row, column - 1);
            if (column < columnMax)
                processCell(grid, visited, queue, row, column + 1);
        }
        return isClosed;
    }

    void processCell(std::vector<std::vector<int>> const &grid, std::vector<std::vector<bool>> &visited, std::queue<std::pair<size_t, size_t>> &queue, size_t row, size_t column) const
    {
        if ((grid[row][column] == LandValue) && (!visited[row][column]))
        {
            visited[row][column] = true;
            queue.emplace(row, column);
        }
    }
};

}

namespace NumberOfClosedIslandsTask
{

TEST(NumberOfClosedIslandsTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.closedIsland({{1, 1, 1, 1, 1, 1, 1, 0},
                                        {1, 0, 0, 0, 0, 1, 1, 0},
                                        {1, 0, 1, 0, 1, 1, 1, 0},
                                        {1, 0, 0, 0, 0, 1, 0, 1},
                                        {1, 1, 1, 1, 1, 1, 1, 0}}));
    ASSERT_EQ(1, solution.closedIsland({{0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 1, 1, 1, 0}}));
    ASSERT_EQ(2, solution.closedIsland({{1, 1, 1, 1, 1, 1, 1},
                                        {1, 0, 0, 0, 0, 0, 1},
                                        {1, 0, 1, 1, 1, 0, 1},
                                        {1, 0, 1, 0, 1, 0, 1},
                                        {1, 0, 1, 1, 1, 0, 1},
                                        {1, 0, 0, 0, 0, 0, 1},
                                        {1, 1, 1, 1, 1, 1, 1}}));
}

}