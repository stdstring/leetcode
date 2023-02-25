#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>> const &matrix) const
    {
        if (matrix.empty())
            return {};
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::vector<int> dest;
        size_t rowLeftBottomStart = 0;
        size_t columnLeftBottomStart = 0;
        size_t rowTopRightStart = 0;
        size_t columnTopRightStart = 0;
        int rowDelta = -1;
        int columnDelta = 1;
        for (size_t index = 0; index < rowCount + columnCount - 1; ++index)
        {
            processDiagonal(matrix, index % 2 == 0 ? rowLeftBottomStart : rowTopRightStart, index % 2 == 0 ? columnLeftBottomStart : columnTopRightStart, rowDelta, columnDelta, dest);
            rowDelta = -rowDelta;
            columnDelta = -columnDelta;
            ++(rowLeftBottomStart < (rowCount - 1) ? rowLeftBottomStart : columnLeftBottomStart);
            ++(columnTopRightStart < (columnCount - 1) ? columnTopRightStart : rowTopRightStart);
        }
        return dest;
    }

private:
    void processDiagonal(std::vector<std::vector<int>> const &matrix, size_t row, size_t column, int rowDelta, int columnDelta, std::vector<int> &dest) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        while (0 <= row && row < rowCount && 0 <= column && column < columnCount)
        {
            dest.push_back(matrix[row][column]);
            row += rowDelta;
            column += columnDelta;
        }
    }
};

}

namespace DiagonalTraverseTask
{

TEST(DiagonalTraverseTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 4, 7, 5, 3, 6, 8, 9}), solution.findDiagonalOrder({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
}

TEST(DiagonalTraverseTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>(), solution.findDiagonalOrder({}));
}

}