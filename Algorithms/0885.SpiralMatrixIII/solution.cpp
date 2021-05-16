#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) const
    {
        const int rowMax = rows - 1;
        const int columnMax = cols - 1;
        std::vector<std::vector<int>> coords;
        const size_t coordsCount = static_cast<size_t>(rows) * cols;
        int length = 1;
        coords.push_back({rStart, cStart});
        int currentRow = rStart;
        int currentColumn = cStart;
        while (coords.size() < coordsCount)
        {
            if (length % 2 == 0)
            {
                // left move
                processRow(currentRow, currentColumn, length, -1, rowMax, columnMax, coords);
                currentColumn -= length;
                // top move
                processColumn(currentRow, length, -1, currentColumn, rowMax, columnMax, coords);
                currentRow -= length;
            }
            else
            {
                // right move
                processRow(currentRow, currentColumn, length, 1, rowMax, columnMax, coords);
                currentColumn += length;
                // bottom move
                processColumn(currentRow, length, 1, currentColumn, rowMax, columnMax, coords);
                currentRow += length;
            }
            ++length;
        }
        return coords;
    }

private:
    void processRow(int row, int columnStart, int length, int step, int rowMax, int columnMax, std::vector<std::vector<int>> &coords) const
    {
        if ((row < 0) || (row > rowMax))
            return;
        const int columnEnd = columnStart + step * length;
        if ((columnStart < 0) && (columnEnd < 0))
            return;
        if ((columnStart > columnMax) && (columnEnd > columnMax))
            return;
        for (int delta = 1; delta <= length; ++delta)
        {
            const int column = columnStart + step * delta;
            if ((0 <= column) && (column <= columnMax))
                coords.push_back({row, column});
        }
    }

    void processColumn(int rowStart, int length, int step, int column, int rowMax, int columnMax, std::vector<std::vector<int>> &coords) const
    {
        if ((column < 0) || (column > columnMax))
            return;
        const int rowEnd = rowStart  + step * length;
        if ((rowStart < 0) && (rowEnd < 0))
            return;
        if ((rowStart > rowMax) && (rowEnd > rowMax))
            return;
        for (int delta = 1; delta <= length; ++delta)
        {
            const int row = rowStart + step * delta;
            if ((0 <= row) && (row <= rowMax))
                coords.push_back({row, column});
        }
    }
};

}

namespace SpiralMatrixIIITask
{

TEST(SpiralMatrixIIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0}, {0, 1}, {0, 2}, {0, 3}}), solution.spiralMatrixIII(1, 4, 0, 0));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 4}, {1, 5}, {2, 5}, {2, 4}, {2, 3}, {1, 3}, {0, 3}, {0, 4}, {0, 5}, {3, 5},
                                             {3, 4}, {3, 3}, {3, 2}, {2, 2}, {1, 2}, {0, 2}, {4, 5}, {4, 4}, {4, 3}, {4, 2},
                                             {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}}), solution.spiralMatrixIII(5, 6, 1, 4));
}

}