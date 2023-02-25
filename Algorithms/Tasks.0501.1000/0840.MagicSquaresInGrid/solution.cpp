#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numMagicSquaresInside(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        if ((rowCount < SquareSize) || (columnCount < SquareSize))
            return 0;
        int magicSquaresCount = 0;
        for (size_t row = 0; row <= rowCount - SquareSize; ++row)
        {
            for (size_t column = 0; column <= columnCount - SquareSize; ++column)
            {
                if (checkIsMagicSquare(grid, row, column))
                    ++magicSquaresCount;
            }
        }
        return magicSquaresCount;
    }

private:
    static constexpr size_t SquareSize = 3;

    bool checkIsMagicSquare(std::vector<std::vector<int>> const &grid, size_t row, size_t column) const
    {
        // check digit presence
        int usedDigits = 0;
        for (size_t rowIndex = 0; rowIndex < SquareSize; ++rowIndex)
        {
            for (size_t columnIndex = 0; columnIndex < SquareSize; ++columnIndex)
            {
                const int value = grid[row + rowIndex][column + columnIndex];
                if ((value < 1) || (value > 9))
                    return false;
                const int mask = 1 << value;
                if ((usedDigits & mask) != 0)
                    return false;
                usedDigits |= mask;
            }
        }
        // check sums
        const int row1Sum = grid[row][column] + grid[row][column + 1] + grid[row][column + 2];
        const int row2Sum = grid[row + 1][column] + grid[row + 1][column + 1] + grid[row + 1][column + 2];
        const int row3Sum = grid[row + 2][column] + grid[row + 2][column + 1] + grid[row + 2][column + 2];
        const int column1Sum = grid[row][column] + grid[row + 1][column] + grid[row + 2][column];
        const int column2Sum = grid[row][column + 1] + grid[row + 1][column + 1] + grid[row + 2][column + 1];
        const int column3Sum = grid[row][column + 2] + grid[row + 1][column + 2] + grid[row + 2][column + 2];
        const int diagonal1Sum = grid[row][column] + grid[row + 1][column + 1] + grid[row + 2][column + 2];
        const int diagonal2Sum = grid[row][column + 2] + grid[row + 1][column + 1] + grid[row + 2][column];
        return (row1Sum == row2Sum) && (row2Sum == row3Sum) && (row3Sum == column1Sum) && (column1Sum == column2Sum) && (column2Sum == column3Sum) && (column3Sum == diagonal1Sum) && (diagonal1Sum == diagonal2Sum);
    }
};

}

namespace MagicSquaresInGridTask
{

TEST(MagicSquaresInGridTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.numMagicSquaresInside({{4, 3, 8, 4}, {9, 5, 1, 9}, {2, 7, 6, 2}}));
    ASSERT_EQ(0, solution.numMagicSquaresInside({{8}}));
    ASSERT_EQ(0, solution.numMagicSquaresInside({{4, 4}, {3, 3}}));
    ASSERT_EQ(0, solution.numMagicSquaresInside({{4, 7, 8}, {9, 5, 1}, {2, 3, 6}}));
}

TEST(MagicSquaresInGridTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.numMagicSquaresInside({{10, 3, 5}, {1, 6, 11}, {7, 9, 2}}));
}

}