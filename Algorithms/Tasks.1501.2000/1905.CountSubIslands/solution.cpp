#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countSubIslands(std::vector<std::vector<int>> const &grid1, std::vector<std::vector<int>> const &grid2) const
    {
        size_t rowCount = grid2.size();
        size_t columnCount = grid2.front().size();
        std::vector<std::vector<bool>> visited(rowCount, std::vector<bool>(columnCount, false));
        size_t subIslandCount = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if ((grid2[row][column] == 0) || visited[row][column])
                    continue;
                if (processIslandInGrid2(grid1, grid2, visited, row, column))
                    ++subIslandCount;
            }
        }
        return static_cast<int>(subIslandCount);
    }

private:
    [[nodiscard]] bool processIslandInGrid2(std::vector<std::vector<int>> const &grid1,
                                            std::vector<std::vector<int>> const &grid2,
                                            std::vector<std::vector<bool>> &visited,
                                            size_t startRow,
                                            size_t startColumn) const
    {
        size_t rowCount = grid2.size();
        size_t columnCount = grid2.front().size();
        std::queue<std::pair<size_t, size_t>> cellQueue;
        cellQueue.emplace(startRow, startColumn);
        visited[startRow][startColumn] = true;
        bool isSubIsland = true;
        while (!cellQueue.empty())
        {
            auto [row, column] = cellQueue.front();
            cellQueue.pop();
            if (grid1[row][column] != 1)
                isSubIsland = false;
            if (row > 0)
                ProcessNextCell(grid2, visited, cellQueue, row - 1, column);
            if (row < (rowCount - 1))
                ProcessNextCell(grid2, visited, cellQueue, row + 1, column);
            if (column > 0)
                ProcessNextCell(grid2, visited, cellQueue, row, column - 1);
            if (column < (columnCount - 1))
                ProcessNextCell(grid2, visited, cellQueue, row, column + 1);
        }
        return isSubIsland;
    }

    void ProcessNextCell(std::vector<std::vector<int>> const &grid2,
                         std::vector<std::vector<bool>> &visited,
                         std::queue<std::pair<size_t, size_t>> &cellQueue,
                         size_t row,
                         size_t column) const
    {
        if ((grid2[row][column] == 1) && !visited[row][column])
        {
            cellQueue.emplace(row, column);
            visited[row][column] = true;
        }
    }
};

}

namespace CountSubIslandsTask
{

TEST(CountSubIslandsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countSubIslands({{1, 1, 1, 0, 0}, {0, 1, 1, 1, 1}, {0, 0, 0, 0, 0}, {1, 0, 0, 0, 0}, {1, 1, 0, 1, 1}},
                                          {{1, 1, 1, 0, 0}, {0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}, {1, 0, 1, 1, 0}, {0, 1, 0, 1, 0}}));
    ASSERT_EQ(2, solution.countSubIslands({{1, 0, 1, 0, 1}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {1, 0, 1, 0, 1}},
                                          {{0, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {0, 1, 0, 1, 0}, {0, 1, 0, 1, 0}, {1, 0, 0, 0, 1}}));
}

}