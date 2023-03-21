#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestMagicSquare(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<long long>> prefixSums(rowCount, std::vector<long long>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                prefixSums[row][column] = (row > 0 ? prefixSums[row - 1][column] : 0) +
                                          (column > 0 ? prefixSums[row][column - 1] : 0) +
                                          grid[row][column] -
                                          ((row > 0) && (column > 0) ? prefixSums[row - 1][column - 1] : 0);
            }
        }
        size_t maxSquareSize = 1;
        for (size_t row = 0; row + maxSquareSize + 1 <= rowCount; ++row)
        {
            for (size_t column = 0; column + maxSquareSize + 1 <= columnCount; ++column)
            {
                for (size_t squareSize = maxSquareSize + 1; (row + squareSize <= rowCount) && (column + squareSize <= columnCount); ++squareSize)
                {
                    const long long squareSum = prefixSums[row + squareSize - 1][column + squareSize - 1] -
                                                (row > 0 ? prefixSums[row - 1][column + squareSize - 1] : 0) -
                                                (column > 0 ? prefixSums[row + squareSize - 1][column - 1] : 0) +
                                                ((row > 0) && (column > 0) ? prefixSums[row - 1][column - 1] : 0);
                    const long long partCount = static_cast<long long>(squareSize);
                    if ((squareSum % partCount) != 0)
                        continue;
                    const long long partSum = squareSum / partCount;
                    if (checkRows(prefixSums, row, column, squareSize, partSum) &&
                        checkColumns(prefixSums, row, column, squareSize, partSum) &&
                        checkDirectDiagonal(grid, row, column, squareSize, partSum) &&
                        checkReverseDiagonal(grid, row, column, squareSize, partSum))
                        maxSquareSize = squareSize;
                }
            }
        }
        return static_cast<int>(maxSquareSize);
    }

private:
    [[nodiscard]] bool checkRows(std::vector<std::vector<long long>> const &prefixSums, size_t rowStart, size_t columnStart, size_t size, long long expectedSum) const
    {
        const size_t rowEnd = rowStart + size - 1;
        const size_t columnEnd = columnStart + size - 1;
        for (size_t row = rowStart; row <= rowEnd; ++row)
        {
            const long long rowSum = prefixSums[row][columnEnd] -
                                     (row > 0 ? prefixSums[row - 1][columnEnd] : 0) -
                                     (columnStart > 0 ? prefixSums[row][columnStart - 1] : 0) +
                                     ((row > 0) && (columnStart > 0) ? prefixSums[row - 1][columnStart - 1] : 0);
            if (rowSum != expectedSum)
                return false;
        }
        return true;
    }

    [[nodiscard]] bool checkColumns(std::vector<std::vector<long long>> const &prefixSums, size_t rowStart, size_t columnStart, size_t size, long long expectedSum) const
    {
        const size_t rowEnd = rowStart + size - 1;
        const size_t columnEnd = columnStart + size - 1;
        for (size_t column = columnStart; column <= columnEnd; ++column)
        {
            const long long columnSum = prefixSums[rowEnd][column] -
                                        (rowStart > 0 ? prefixSums[rowStart - 1][column] : 0) -
                                        (column > 0 ? prefixSums[rowEnd][column - 1] : 0) +
                                        ((rowStart > 0) && (column > 0) ? prefixSums[rowStart - 1][column - 1] : 0);
            if (columnSum != expectedSum)
                return false;
        }
        return true;
    }

    [[nodiscard]] bool checkDirectDiagonal(std::vector<std::vector<int>> const &grid, size_t row, size_t column, size_t diagonalSize, long long expectedSum) const
    {
        long long diagonalSum = 0;
        for (size_t size = 0; size < diagonalSize; ++size)
            diagonalSum += grid[row + size][column + size];
        return diagonalSum == expectedSum;
    }

    [[nodiscard]] bool checkReverseDiagonal(std::vector<std::vector<int>> const &grid, size_t row, size_t column, size_t diagonalSize, long long expectedSum) const
    {
        long long diagonalSum = 0;
        for (size_t size = 0; size < diagonalSize; ++size)
            diagonalSum += grid[row + size][column + diagonalSize - 1 - size];
        return diagonalSum == expectedSum;
    }
};

}

namespace LargestMagicSquareTask
{

TEST(LargestMagicSquareTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.largestMagicSquare({{7, 1, 4, 5, 6}, {2, 5, 1, 6, 4}, {1, 5, 4, 3, 2}, {1, 2, 7, 3, 4}}));
    ASSERT_EQ(2, solution.largestMagicSquare({{5, 1, 3, 1}, {9, 3, 3, 1}, {1, 3, 3, 8}}));
}

TEST(LargestMagicSquareTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.largestMagicSquare({{1, 2, 1, 1}, {2, 1, 1, 1}, {3, 2, 2, 3}, {1, 3, 3, 3}}));
}

}