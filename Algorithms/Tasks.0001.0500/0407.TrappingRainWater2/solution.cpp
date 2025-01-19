#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int trapRainWater(std::vector<std::vector<int>> const &heightMap) const
    {
        const size_t rowCount = heightMap.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = heightMap.front().size();
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<CellState>> cells(rowCount, std::vector<CellState>(columnCount, CellState::Unprocessed));
        std::multimap<int, CellData> cellQueue;
        // init border
        for (size_t column = 0; column < columnCount; ++column)
        {
            cells[0][column] = CellState::InBorder;
            cellQueue.emplace(heightMap[0][column], CellData(0, column));
            if (rowMax > 0)
            {
                cells[rowMax][column] = CellState::InBorder;
                cellQueue.emplace(heightMap[rowMax][column], CellData(rowMax, column));
            }
        }
        for (size_t row = 1; row < rowMax; ++row)
        {
            cells[row][0] = CellState::InBorder;
            cellQueue.emplace(heightMap[row][0], CellData(row, 0));
            if (columnMax > 0)
            {
                cells[row][columnMax] = CellState::InBorder;
                cellQueue.emplace(heightMap[row][columnMax], CellData(row, columnMax));
            }
        }
        // process
        int result = 0;
        while (!cellQueue.empty())
        {
            int minHeight = cellQueue.cbegin()->first;
            CellData current(cellQueue.cbegin()->second);
            cellQueue.erase(cellQueue.cbegin());
            if (current.Column > 0)
                result += processNextCell(current.Row, current.Column - 1, minHeight, heightMap, cellQueue, cells);
            if (current.Column < columnMax)
                result += processNextCell(current.Row, current.Column + 1, minHeight, heightMap, cellQueue, cells);
            if (current.Row > 0)
                result += processNextCell(current.Row - 1, current.Column, minHeight, heightMap, cellQueue, cells);
            if (current.Row < rowMax)
                result += processNextCell(current.Row + 1, current.Column, minHeight, heightMap, cellQueue, cells);
            cells[current.Row][current.Column] = CellState::Processed;
        }
        return result;
    }

private:
    struct CellData
    {
        CellData(size_t row, size_t column) : Row(row), Column(column)
        {
        }
        size_t Row;
        size_t Column;
    };

    enum class CellState {Unprocessed, InBorder, Processed};

    [[nodiscard]] int processNextCell(size_t row,
                                      size_t column,
                                      int minHeight,
                                      std::vector<std::vector<int>> const &heightMap,
                                      std::multimap<int, CellData> &cellQueue,
                                      std::vector<std::vector<CellState>> &cells) const
    {
        if (cells[row][column] != CellState::Unprocessed)
            return 0;
        cells[row][column] = CellState::InBorder;
        if (heightMap[row][column] < minHeight)
        {
            cellQueue.emplace(minHeight, CellData(row, column));
            return minHeight - heightMap[row][column];
        }
        cellQueue.emplace(heightMap[row][column], CellData(row, column));
        return 0;
    }
};

}

namespace TrappingRainWater2Task
{

TEST(TrappingRainWater2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.trapRainWater({{1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}}));
    ASSERT_EQ(10, solution.trapRainWater({{3, 3, 3, 3, 3}, {3, 2, 2, 2, 3}, {3, 2, 1, 2, 3}, {3, 2, 2, 2, 3}, {3, 3, 3, 3, 3}}));
}

}