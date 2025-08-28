#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> sortMatrix(std::vector<std::vector<int>> const &grid) const
    {
        const size_t n = grid.size();
        std::vector<std::vector<int>> result(n, std::vector<int>(n));
        // bottom-left triangle
        for (size_t row = 0; row < n; ++row)
            processDiagonal(grid, result, row, 0);
        // top - right triangle
        for (size_t column = 1; column < n; ++column)
            processDiagonal(grid, result, 0, column);
        return result;
    }

private:
    typedef std::vector<std::vector<int>> TMatrix;

    void processDiagonal(TMatrix const &source, TMatrix &dest, size_t row, size_t column) const
    {
        const size_t n = source.size();
        const size_t diagonalSize = column == 0 ? n - row : n - column;
        std::vector<int> diagonal(diagonalSize);
        for (size_t shift = 0; shift < diagonalSize; ++shift)
            diagonal[shift] = source[row + shift][column + shift];
        auto comparator = [column](int left, int right) { return (column == 0) ? (left > right) : (left < right); };
        std::ranges::sort(diagonal, comparator);
        for (size_t shift = 0; shift < diagonalSize; ++shift)
            dest[row + shift][column + shift] = diagonal[shift];
    }
};

}

namespace SortMatrixByDiagonalsTask
{

TEST(SortMatrixByDiagonalsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{8, 2, 3}, {9, 6, 7}, {4, 5, 1}}),
              solution.sortMatrix({{1, 7, 3}, {9, 8, 2}, {4, 5, 6}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{2, 1}, {1, 0}}), solution.sortMatrix({{0, 1}, {1, 2}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1}}), solution.sortMatrix({{1}}));
}

}