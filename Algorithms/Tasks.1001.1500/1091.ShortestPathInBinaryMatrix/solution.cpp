#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int shortestPathBinaryMatrix(std::vector<std::vector<int>> const &grid) const
    {
        if (grid[0][0] != 0)
            return -1;
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<int>> paths(rowCount, std::vector<int>(columnCount, -1));
        std::queue<std::pair<int, int>> queue;
        paths[0][0] = 1;
        queue.emplace(0, 0);
        while (!queue.empty())
        {
            const int currentRow = queue.front().first;
            const int currentColumn = queue.front().second;
            queue.pop();
            processAdjacentCell(currentRow, currentColumn, currentRow, currentColumn - 1, grid, paths, queue);
            processAdjacentCell(currentRow, currentColumn, currentRow, currentColumn + 1, grid, paths, queue);
            processAdjacentCell(currentRow, currentColumn, currentRow - 1, currentColumn, grid, paths, queue);
            processAdjacentCell(currentRow, currentColumn, currentRow + 1, currentColumn, grid, paths, queue);
            processAdjacentCell(currentRow, currentColumn, currentRow - 1, currentColumn - 1, grid, paths, queue);
            processAdjacentCell(currentRow, currentColumn, currentRow - 1, currentColumn + 1, grid, paths, queue);
            processAdjacentCell(currentRow, currentColumn, currentRow + 1, currentColumn - 1, grid, paths, queue);
            processAdjacentCell(currentRow, currentColumn, currentRow + 1, currentColumn + 1, grid, paths, queue);
        }
        return paths.back().back();
    }

private:
    void processAdjacentCell(int currentRow,
                             int currentColumn,
                             int nextRow,
                             int nextColumn,
                             std::vector<std::vector<int>> const &grid,
                             std::vector<std::vector<int>> &paths,
                             std::queue<std::pair<int, int>> &queue) const
    {
        const int rowMax = static_cast<int>(grid.size() - 1);
        const int columnMax = static_cast<int>(grid.front().size() - 1);
        if ((nextRow < 0) || (nextColumn < 0) || (nextRow > rowMax) || (nextColumn > columnMax))
            return;
        if (grid[nextRow][nextColumn] != 0)
            return;
        const int nextLength = paths[currentRow][currentColumn] + 1;
        if ((paths[nextRow][nextColumn] != -1) && (paths[nextRow][nextColumn] <= nextLength))
            return;
        paths[nextRow][nextColumn] = nextLength;
        queue.emplace(nextRow, nextColumn);
    }
};

}

namespace ShortestPathInBinaryMatrixTask
{

TEST(ShortestPathInBinaryMatrixTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.shortestPathBinaryMatrix({{0, 1}, {1, 0}}));
    ASSERT_EQ(4, solution.shortestPathBinaryMatrix({{0, 0, 0}, {1, 1, 0}, {1, 1, 0}}));
    ASSERT_EQ(-1, solution.shortestPathBinaryMatrix({{1, 0, 0}, {1, 1, 0}, {1, 1, 0}}));
}

}
