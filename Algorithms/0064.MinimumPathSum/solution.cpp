#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minPathSum(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<int>> sumData(rowCount, std::vector<int>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (row == 0 && column == 0)
                    sumData[row][column] = grid[row][column];
                else if (row == 0 && column != 0)
                    sumData[row][column] = sumData[row][column - 1] + grid[row][column];
                else if (row != 0 && column == 0)
                    sumData[row][column] = sumData[row - 1][column] + grid[row][column];
                else
                    sumData[row][column] = std::min(sumData[row][column - 1], sumData[row - 1][column]) + grid[row][column];
            }
        }
        return sumData.back().back();
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