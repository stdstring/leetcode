#include <algorithm>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> maxPoints(std::vector<std::vector<int>> const &grid, std::vector<int> const &queries) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<size_t> indexes(queries.size(), 0);
        std::iota(indexes.begin(), indexes.end(), 0);
        std::ranges::sort(indexes, [&queries](size_t left, size_t right) { return queries[left] < queries[right]; });
        std::vector<int> result(queries.size(), 0);
        int currentValue = 0;
        int currentCount = 0;
        std::vector<std::vector<CellColor>> colors(rowCount, std::vector<CellColor>(columnCount, CellColor::White));
        std::queue<TCell> startCells({TCell(0, 0)});
        colors[0][0] = CellColor::Gray;
        for (const size_t index : indexes)
        {
            if (queries[index] == currentValue)
            {
                result[index] = currentCount;
                continue;
            }
            currentValue = queries[index];
            auto [processed, nextCell] = processMoves(startCells, grid, colors, currentValue);
            currentCount += processed;
            result[index] = currentCount;
            std::swap(startCells, nextCell);
        }
        return result;
    }

private:
    enum class CellColor {White, Gray, Black};

    typedef std::pair<size_t, size_t> TCell;

    [[nodiscard]] std::pair<int, std::queue<TCell>> processMoves(std::queue<TCell> const &startCells,
                                                                 std::vector<std::vector<int>> const &grid,
                                                                 std::vector<std::vector<CellColor>> &colors,
                                                                 int value) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        int processed = 0;
        std::queue<TCell> queue(startCells);
        std::queue<TCell> nextCells;
        while (!queue.empty())
        {
            auto [row, column] = queue.front();
            queue.pop();
            if (colors[row][column] == CellColor::Black)
                continue;
            if (grid[row][column] >= value)
            {
                nextCells.emplace(row, column);
                continue;
            }
            ++processed;
            colors[row][column] = CellColor::Black;
            if ((row > 0) && (colors[row - 1][column] == CellColor::White))
                addNextCell(row - 1, column, queue, colors);
            if ((row < rowMax) && (colors[row + 1][column] == CellColor::White))
                addNextCell(row + 1, column, queue, colors);
            if ((column > 0) && (colors[row][column - 1] == CellColor::White))
                addNextCell(row, column - 1, queue, colors);
            if ((column < columnMax) && (colors[row][column + 1] == CellColor::White))
                addNextCell(row, column + 1, queue, colors);
        }
        return {processed, nextCells};
    }

    void addNextCell(size_t row, size_t column, std::queue<TCell> &queue, std::vector<std::vector<CellColor>> &colors) const
    {
        queue.emplace(row, column);
        colors[row][column] = CellColor::Gray;
    }
};

}

namespace MaxNumberPointsFromGridQueriesTask
{

TEST(MaxNumberPointsFromGridQueriesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({5, 8, 1}), solution.maxPoints({{1, 2, 3}, {2, 5, 7}, {3, 5, 1}}, {5, 6, 2}));
    ASSERT_EQ(std::vector<int>({0}), solution.maxPoints({{5, 2, 1}, {1, 1, 2}}, {3}));
}

}