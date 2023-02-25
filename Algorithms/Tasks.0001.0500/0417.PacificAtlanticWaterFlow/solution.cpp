#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

enum class CellStatus {None = 0, Pacific = 1, Atlantic = 2, Both = 3, InProgress = 4};

CellStatus operator| (CellStatus a, CellStatus b)
{
    return static_cast<CellStatus>(static_cast<int>(a) | static_cast<int>(b));
}

CellStatus& operator|= (CellStatus &a, CellStatus b)
{
    a = a | b;
    return a;
}

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>> const &heights) const
    {
        auto cmp = [&heights](std::pair<size_t, size_t> const &l, std::pair<size_t, size_t> const &r) { return heights[l.first][l.second] > heights[r.first][r.second]; };
        std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, decltype(cmp)> queue(cmp);
        for (size_t row = 0; row < heights.size(); ++row)
        {
            for (size_t column = 0; column < heights.front().size(); ++column)
                queue.emplace(row, column);
        }
        std::vector<std::vector<int>> result;
        const size_t rowCount = heights.size();
        const size_t columnCount = heights.front().size();
        std::vector<CellStatus> cells(rowCount * columnCount, CellStatus::None);
        while (!queue.empty())
        {
            const size_t row = queue.top().first;
            const size_t column = queue.top().second;
            const int height = heights[row][column];
            const size_t cellIndex = row * heights.front().size() + column;
            if (cells[cellIndex] == CellStatus::None)
                writeStatus(cells, row, column, rowCount, columnCount, calcTotalStatus(heights, cells, row, column, height, CellStatus::None));
            if (cells[cellIndex] == CellStatus::Both)
                result.push_back(std::vector<int>({static_cast<int>(row), static_cast<int>(column)}));
            queue.pop();
        }
        return result;
    }

private:
    CellStatus calcTotalStatus(std::vector<std::vector<int>> const &heights, std::vector<CellStatus> &cells, size_t row, size_t column, int height, CellStatus status) const
    {
        const size_t cellIndex = row * heights.front().size() + column;
        if (heights[row][column] < height)
            return cells[cellIndex];
        if (cells[cellIndex] == CellStatus::InProgress)
            return CellStatus::None;
        cells[cellIndex] = CellStatus::InProgress;
        const size_t rowMax = heights.size() - 1;
        const size_t columnMax = heights.front().size() - 1;
        CellStatus currentStatus = status;
        if ((row == 0) || (column == 0))
            currentStatus |= CellStatus::Pacific;
        if ((row == rowMax) || (column == columnMax))
            currentStatus |= CellStatus::Atlantic;
        if ((row > 0) && (heights[row - 1][column] <= height))
            currentStatus |= calcTotalStatus(heights, cells, row - 1, column, height, currentStatus);
        if ((column > 0) && (heights[row][column - 1] <= height))
            currentStatus |= calcTotalStatus(heights, cells, row, column - 1, height, currentStatus);
        if ((row < rowMax) && (heights[row + 1][column] <= height))
            currentStatus |= calcTotalStatus(heights, cells, row + 1, column, height, currentStatus);
        if ((column < columnMax) && (heights[row][column + 1] <= height))
            currentStatus |= calcTotalStatus(heights, cells, row, column + 1, height, currentStatus);
        return currentStatus;
    }

    void writeStatus(std::vector<CellStatus> &cells, size_t row, size_t column, size_t rowCount, size_t columnCount, CellStatus status) const
    {
        const size_t cellIndex = row * columnCount + column;
        if (cells[cellIndex] != CellStatus::InProgress)
            return;
        cells[cellIndex] = status;
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        if (row > 0)
            writeStatus(cells, row - 1, column, rowCount, columnCount, status);
        if (column > 0)
            writeStatus(cells, row, column - 1, rowCount, columnCount, status);
        if (row < rowMax)
            writeStatus(cells, row + 1, column, rowCount, columnCount, status);
        if (column < columnMax)
            writeStatus(cells, row, column + 1, rowCount, columnCount, status);
    }
};

}

namespace PacificAtlanticWaterFlowTask
{

TEST(PacificAtlanticWaterFlowTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 4}, {1, 3}, {2, 2}, {0, 4}, {4, 0}, {3, 0}, {3, 1}}),
              solution.pacificAtlantic({{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0}}), solution.pacificAtlantic({{1}}));
}

}
