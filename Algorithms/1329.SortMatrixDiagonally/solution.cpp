#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> diagonalSort(std::vector<std::vector<int>> const &mat) const
    {
        std::vector<std::vector<int>> dest(mat);
        // main diagonal
        sortDiagonal(mat, 0, 0, dest);
        // other diagonals with row = 0
        for (size_t column = 1; column < mat.front().size(); ++column)
            sortDiagonal(mat, 0, column, dest);
        // other diagonals with column = 0
        for (size_t row = 1; row < mat.size(); ++row)
            sortDiagonal(mat, row, 0, dest);
        return dest;
    }

private:
    [[nodiscard]] std::vector<int> getDiagonal(std::vector<std::vector<int>> const &source, size_t rowStart, size_t columnStart) const
    {
        const size_t rowCount = source.size();
        const size_t columnCount = source.front().size();
        std::vector<int> diagonal;
        for (size_t row = rowStart, column = columnStart; (row < rowCount) && (column < columnCount); ++row, ++column)
            diagonal.push_back(source[row][column]);
        return diagonal;
    }

    void setDiagonal(std::vector<std::vector<int>> &dest, size_t rowStart, size_t columnStart, std::vector<int> const &diagonal) const
    {
        for (size_t row = rowStart, column = columnStart, index = 0; index < diagonal.size(); ++row, ++column, ++index)
            dest[row][column] = diagonal[index];
    }

    void sortDiagonal(std::vector<std::vector<int>> const &source, size_t rowStart, size_t columnStart, std::vector<std::vector<int>> &dest) const
    {
        std::vector<int> diagonal(getDiagonal(source, rowStart, columnStart));
        std::sort(diagonal.begin(), diagonal.end());
        setDiagonal(dest, rowStart, columnStart, diagonal);
    }
};

}

namespace SortMatrixDiagonallyTask
{

TEST(SortMatrixDiagonallyTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1, 1, 1}, {1, 2, 2, 2}, {1, 2, 3, 3}}), solution.diagonalSort({{3, 3, 1, 1}, {2, 2, 1, 2}, {1, 1, 1, 2}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{5, 17, 4, 1, 52, 7}, {11, 11, 25, 45, 8, 69}, {14, 23, 25, 44, 58, 15}, {22, 27, 31, 36, 50, 66}, {84, 28, 75, 33, 55, 68}}),
              solution.diagonalSort({{11, 25, 66, 1, 69, 7}, {23, 55, 17, 45, 15, 52}, {75, 31, 36, 44, 58, 8}, {22, 27, 33, 25, 68, 4}, {84, 28, 14, 11, 5, 50}}));
}

}