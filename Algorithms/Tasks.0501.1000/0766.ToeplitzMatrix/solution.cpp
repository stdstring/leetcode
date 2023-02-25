#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isToeplitzMatrix(std::vector<std::vector<int>> const &matrix) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        // move left
        for (size_t column = 0; column < columnCount; ++column)
        {
            if (!checkDiagonal(matrix, 0, column))
                return false;
        }
        // move bottom
        for (size_t row = 1; row < rowCount; ++row)
        {
            if (!checkDiagonal(matrix, row, 0))
                return false;
        }
        return true;
    }

private:
    bool checkDiagonal(std::vector<std::vector<int>> const &matrix, size_t startRow, size_t startColumn) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        const int value = matrix[startRow][startColumn];
        for (size_t row = startRow, column = startColumn; row < rowCount && column < columnCount; ++row, ++column)
        {
            if (matrix[row][column] != value)
                return false;
        }
        return true;
    }
};

}

namespace ToeplitzMatrixTask
{

TEST(ToeplitzMatrixTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isToeplitzMatrix({{1, 2, 3, 4}, {5, 1, 2, 3}, {9, 5, 1, 2}}));
    ASSERT_EQ(false, solution.isToeplitzMatrix({{1, 2}, {2, 2}}));
}

}