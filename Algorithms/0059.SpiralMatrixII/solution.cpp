#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> generateMatrix(int n) const
    {
        std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
        int row = 0;
        int column = 0;
        int deltaRow = 0;
        int deltaColumn = 1;
        for (int number = 1; number <= n * n; ++number)
        {
            if (deltaRow == 1 && (row == n || result[row][column] != 0))
            {
                --row;
                --column;
                deltaRow = 0;
                deltaColumn = -1;
            }
            else if (deltaRow == -1 && (row < 0 || result[row][column] != 0))
            {
                ++row;
                ++column;
                deltaRow = 0;
                deltaColumn = 1;
            }
            else if (deltaColumn == 1 && (column == n || result[row][column] != 0))
            {
                --column;
                ++row;
                deltaRow = 1;
                deltaColumn = 0;
            }
            else if (deltaColumn == -1 && (column < 0 || result[row][column] != 0))
            {
                ++column;
                --row;
                deltaRow = -1;
                deltaColumn = 0;
            }
            result[row][column] = number;
            row += deltaRow;
            column += deltaColumn;
        }
        return result;
    }
};

}

namespace SpiralMatrixIITask
{

TEST(SpiralMatrixIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 3}, {8, 9, 4}, {7, 6, 5}}), solution.generateMatrix(3));
}

}