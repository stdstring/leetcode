#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestIsland(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<CellData>> cells(rowCount, std::vector<CellData>(columnCount, CellData()));
        std::vector<Island> islands;
        int islandId = 1;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if ((grid[row][column] == 1) && (cells[row][column].Size == 0))
                    islands.emplace_back(processIsland(grid, row, column, islandId++, cells));
            }
        }
        if (islands.empty())
            return 1;
        size_t bestResult = 0;
        for (Island const &island : islands)
        {
            bestResult = std::max(bestResult, island.Size);
            for (auto const& [row, column] : island.Border)
                bestResult = std::max(bestResult, calcForBorder(grid, row, column, cells));
        }
        return static_cast<int>(bestResult);
    }

private:
    struct CellData
    {
        CellData() = default;

        CellData(size_t parentRow, size_t parentColumn, size_t size, int islandId) : ParentRow(parentRow), ParentColumn(parentColumn), Size(size), IslandId(islandId)
        {
        }

        size_t ParentRow = 0;
        size_t ParentColumn = 0;
        size_t Size = 0;
        int IslandId = 0;
    };

    typedef std::pair<size_t, size_t> TCell;

    struct Island
    {
        Island(TCell const &startPoint, size_t size, std::vector<TCell> const &border) : StartPoint(startPoint), Size(size), Border(border)
        {
        }

        TCell StartPoint;
        size_t Size;
        std::vector<TCell> Border;
    };

    [[nodiscard]] bool isBorderCell(std::vector<std::vector<int>> const &grid, size_t row, size_t column) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        return (grid[row][column] == 1) &&
               (((row > 0) && (grid[row - 1][column] == 0)) ||
               ((row < rowMax) && (grid[row + 1][column] == 0)) ||
               ((column > 0) && (grid[row][column - 1] == 0)) ||
               ((column < columnMax) && (grid[row][column + 1] == 0)));
    }

    [[nodiscard]] Island processIsland(std::vector<std::vector<int>> const &grid, size_t startRow, size_t startColumn, int islandId, std::vector<std::vector<CellData>> &cells) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        const TCell startCell(startRow, startColumn);
        size_t islandSize = 0;
        std::vector<TCell> border;
        std::queue<TCell> queue;
        cells[startRow][startColumn] = CellData(startRow, startColumn, 1, islandId);
        queue.emplace(startRow, startColumn);
        while (!queue.empty())
        {
            auto [row, column] = queue.front();
            queue.pop();
            ++islandSize;
            if (isBorderCell(grid, row, column))
                border.emplace_back(row, column);
            if ((row > 0) && (grid[row - 1][column] == 1) && (cells[row - 1][column].Size == 0))
            {
                cells[row - 1][column] = CellData(startRow, startColumn, 1, islandId);
                queue.emplace(row - 1, column);
            }
            if ((row < rowMax) && (grid[row + 1][column] == 1) && (cells[row + 1][column].Size == 0))
            {
                cells[row + 1][column] = CellData(startRow, startColumn, 1, islandId);
                queue.emplace(row + 1, column);
            }
            if ((column > 0) && (grid[row][column - 1] == 1) && (cells[row][column - 1].Size == 0))
            {
                cells[row][column - 1] = CellData(startRow, startColumn, 1, islandId);
                queue.emplace(row, column - 1);
            }
            if ((column < columnMax) && (grid[row][column + 1] == 1) && (cells[row][column + 1].Size == 0))
            {
                cells[row][column + 1] = CellData(startRow, startColumn, 1, islandId);
                queue.emplace(row, column + 1);
            }
        }
        cells[startRow][startColumn].Size = islandSize;
        return Island(startCell, islandSize, border);
    }

    [[nodiscard]] size_t calcForBorder(std::vector<std::vector<int>> const &grid, size_t borderRow, size_t borderColumn, std::vector<std::vector<CellData>> const &cells) const
    {
        size_t result = 0;
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        if ((borderRow > 0) && (grid[borderRow - 1][borderColumn] == 0))
            result = std::max(result, calcForCell(grid, borderRow - 1, borderColumn, cells));
        if ((borderRow < rowMax) && (grid[borderRow + 1][borderColumn] == 0))
            result = std::max(result, calcForCell(grid, borderRow + 1, borderColumn, cells));
        if ((borderColumn > 0) && (grid[borderRow][borderColumn - 1] == 0))
            result = std::max(result, calcForCell(grid, borderRow, borderColumn - 1, cells));
        if ((borderColumn < columnMax) && (grid[borderRow][borderColumn + 1] == 0))
            result = std::max(result, calcForCell(grid, borderRow, borderColumn + 1, cells));
        return result;
    }

    [[nodiscard]] size_t calcForCell(std::vector<std::vector<int>> const &grid, size_t row, size_t column, std::vector<std::vector<CellData>> const &cells) const
    {
        const size_t rowMax = grid.size() - 1;
        const size_t columnMax = grid.front().size() - 1;
        size_t result = 1;
        std::unordered_set<int> usedIslands;
        if ((row > 0) && (grid[row - 1][column] == 1))
        {
            auto [parentRow, parentColumn, size, islandId] = cells[row - 1][column];
            if (!usedIslands.contains(islandId))
            {
                result += cells[parentRow][parentColumn].Size;
                usedIslands.emplace(islandId);
            }
        }
        if ((row < rowMax) && (grid[row + 1][column] == 1))
        {
            auto [parentRow, parentColumn, size, islandId] = cells[row + 1][column];
            if (!usedIslands.contains(islandId))
            {
                result += cells[parentRow][parentColumn].Size;
                usedIslands.emplace(islandId);
            }
        }
        if ((column > 0) && (grid[row][column - 1] == 1))
        {
            auto [parentRow, parentColumn, size, islandId] = cells[row][column - 1];
            if (!usedIslands.contains(islandId))
            {
                result += cells[parentRow][parentColumn].Size;
                usedIslands.emplace(islandId);
            }
        }
        if ((column < columnMax) && (grid[row][column + 1] == 1))
        {
            auto [parentRow, parentColumn, size, islandId] = cells[row][column + 1];
            if (!usedIslands.contains(islandId))
            {
                result += cells[parentRow][parentColumn].Size;
                usedIslands.emplace(islandId);
            }
        }
        return result;
    }
};

}

namespace MakingLargeIslandTask
{

TEST(MakingLargeIslandTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.largestIsland({{1, 0}, {0, 1}}));
    ASSERT_EQ(4, solution.largestIsland({{1, 1}, {1, 0}}));
    ASSERT_EQ(4, solution.largestIsland({{1, 1}, {1, 1}}));
}

TEST(MakingLargeIslandTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.largestIsland({{0, 0}, {0, 0}}));
}

}