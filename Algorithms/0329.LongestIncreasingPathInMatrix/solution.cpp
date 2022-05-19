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
    [[nodiscard]] int longestIncreasingPath(std::vector<std::vector<int>> const &matrix) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::vector<std::vector<int>> paths(rowCount, std::vector<int>(columnCount, 1));
        std::queue<std::pair<int, int>> queue;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                queue.emplace(row, column);
        }
        while (!queue.empty())
        {
            const int currentRow = queue.front().first;
            const int currentColumn = queue.front().second;
            queue.pop();
            processNext(currentRow, currentColumn, currentRow, currentColumn - 1, matrix, paths, queue);
            processNext(currentRow, currentColumn, currentRow, currentColumn + 1, matrix, paths, queue);
            processNext(currentRow, currentColumn, currentRow - 1, currentColumn, matrix, paths, queue);
            processNext(currentRow, currentColumn, currentRow + 1, currentColumn, matrix, paths, queue);
        }
        int longestPath = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                longestPath = std::max(longestPath, paths[row][column]);
        }
        return longestPath;
    }

private:
    void processNext(int currentRow,
                     int currentColumn,
                     int nextRow,
                     int nextColumn,
                     std::vector<std::vector<int>> const &matrix,
                     std::vector<std::vector<int>> &paths,
                     std::queue<std::pair<int, int>> &queue) const
    {
        const int rowMax = static_cast<int>(matrix.size() - 1);
        const int columnMax = static_cast<int>(matrix.front().size() - 1);
        if ((nextRow < 0) || (nextRow > rowMax))
            return;
        if ((nextColumn < 0) || (nextColumn > columnMax))
            return;
        if (matrix[currentRow][currentColumn] >= matrix[nextRow][nextColumn])
            return;
        const int currentPath = paths[currentRow][currentColumn];
        const int nextPath = paths[nextRow][nextColumn];
        if ((currentPath + 1) <= nextPath)
            return;
        paths[nextRow][nextColumn] = currentPath + 1;
        queue.emplace(nextRow, nextColumn);
    }
};

}

namespace LongestIncreasingPathInMatrixTask
{

TEST(LongestIncreasingPathInMatrixTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.longestIncreasingPath({{9, 9, 4}, {6, 6, 8}, {2, 1, 1}}));
    ASSERT_EQ(4, solution.longestIncreasingPath({{3, 4, 5}, {3, 2, 6}, {2, 2, 1}}));
    ASSERT_EQ(1, solution.longestIncreasingPath({{1}}));
}

}