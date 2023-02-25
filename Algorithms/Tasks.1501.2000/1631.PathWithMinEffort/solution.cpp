#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumEffortPath(std::vector<std::vector<int>> const &heights) const
    {
        const size_t rowCount = heights.size();
        const size_t maxRow = rowCount - 1;
        const size_t columnCount = heights.front().size();
        const size_t maxColumn = columnCount - 1;
        std::vector<std::vector<int>> efforts(rowCount, std::vector<int>(columnCount, INT_MAX));
        std::queue<std::pair<size_t, size_t>> cells;
        efforts[0][0] = 0;
        cells.emplace(0, 0);
        while (!cells.empty())
        {
            const size_t currentRow = cells.front().first;
            const size_t currentColumn = cells.front().second;
            cells.pop();
            if (currentRow > 0)
                processNextCell(currentRow, currentColumn, currentRow - 1, currentColumn, heights, efforts, cells);
            if (currentColumn > 0)
                processNextCell(currentRow, currentColumn, currentRow, currentColumn - 1, heights, efforts, cells);
            if (currentRow < maxRow)
                processNextCell(currentRow, currentColumn, currentRow + 1, currentColumn, heights, efforts, cells);
            if (currentColumn < maxColumn)
                processNextCell(currentRow, currentColumn, currentRow, currentColumn + 1, heights, efforts, cells);
        }
        return efforts.back().back();
    }

private:
    void processNextCell(size_t currentRow,
                         size_t currentColumn,
                         size_t nextRow,
                         size_t nextColumn,
                         std::vector<std::vector<int>> const &heights,
                         std::vector<std::vector<int>> &efforts,
                         std::queue<std::pair<size_t, size_t>> &cells) const
    {
        const int currentEffort = efforts[currentRow][currentColumn];
        const int nextEffort = efforts[nextRow][nextColumn];
        const int heightDiff = std::abs(heights[currentRow][currentColumn] - heights[nextRow][nextColumn]);
        const int maxEffort = std::max(currentEffort, heightDiff);
        if (maxEffort < nextEffort)
        {
            efforts[nextRow][nextColumn] = maxEffort;
            cells.emplace(nextRow, nextColumn);
        }
    }
};

}

namespace PathWithMinEffortTask
{

TEST(PathWithMinEffortTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.minimumEffortPath({{1, 2, 2}, {3, 8, 2}, {5, 3, 5}}));
    ASSERT_EQ(1, solution.minimumEffortPath({{1, 2, 3}, {3, 8, 4}, {5, 3, 5}}));
    ASSERT_EQ(0, solution.minimumEffortPath({{1, 2, 1, 1, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 1, 1, 2, 1}}));
}

}