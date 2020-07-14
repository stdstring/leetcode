#include <deque>
#include <limits>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct CellCoord
{
    CellCoord(int row, int column) : Row(row), Column(column)
    {
    }

    int Row;
    int Column;
};

class Solution
{
public:
    int minPathSum(std::vector<std::vector<int>> const &grid) const
    {
        const int rowCount = grid.size();
        const int columnCount = grid.front().size();
        std::vector<std::vector<int>> pathData(rowCount, std::vector<int>(columnCount, std::numeric_limits<int>::max()));
        pathData[0][0] = grid[0][0];
        std::deque<CellCoord> cells;
        cells.emplace_back(0, 0);
        while (!cells.empty())
        {
            int row = cells.front().Row;
            int column = cells.front().Column;
            if (row < (rowCount - 1))
            {
                const int currentSum = pathData[row][column] + grid[row + 1][column];
                if (currentSum < pathData[row + 1][column])
                {
                    pathData[row + 1][column] = currentSum;
                    cells.emplace_back(row + 1, column);
                }
            }
            if (column < (columnCount - 1))
            {
                const int currentSum = pathData[row][column] + grid[row][column + 1];
                if (currentSum < pathData[row][column + 1])
                {
                    pathData[row][column + 1] = currentSum;
                    cells.emplace_back(row, column + 1);
                }
            }
            cells.pop_front();
        }
        return pathData.back().back();
    }
};

}

namespace MinimumPathSumTask
{

TEST(MinimumPathSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(7, solution.minPathSum({{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}));
}

TEST(MinimumPathSumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(85, solution.minPathSum({{7, 1, 3, 5, 8, 9, 9, 2, 1, 9, 0, 8, 3, 1, 6, 6, 9, 5},
                                       {9, 5, 9, 4, 0, 4, 8, 8, 9, 5, 7, 3, 6, 6, 6, 9, 1, 6},
                                       {8, 2, 9, 1, 3, 1, 9, 7, 2, 5, 3, 1, 2, 4, 8, 2, 8, 8},
                                       {6, 7, 9, 8, 4, 8, 3, 0, 4, 0, 9, 6, 6, 0, 0, 5, 1, 4},
                                       {7, 1, 3, 1, 8, 8, 3, 1, 2, 1, 5, 0, 2, 1, 9, 1, 1, 4},
                                       {9, 5, 4, 3, 5, 6, 1, 3, 6, 4, 9, 7, 0, 8, 0, 3, 9, 9},
                                       {1, 4, 2, 5, 8, 7, 7, 0, 0, 7, 1, 2, 1, 2, 7, 7, 7, 4},
                                       {3, 9, 7, 9, 5, 8, 9, 5, 6, 9, 8, 8, 0, 1, 4, 2, 8, 2},
                                       {1, 5, 2, 2, 2, 5, 6, 3, 9, 3, 1, 7, 9, 6, 8, 6, 8, 3},
                                       {5, 7, 8, 3, 8, 8, 3, 9, 9, 8, 1, 9, 2, 5, 4, 7, 7, 7},
                                       {2, 3, 2, 4, 8, 5, 1, 7, 2, 9, 5, 2, 4, 2, 9, 2, 8, 7},
                                       {0, 1, 6, 1, 1, 0, 0, 6, 5, 4, 3, 4, 3, 7, 9, 6, 1, 9}}));
}

}