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
        const int rowCount = matrix.size();
        const int columnCount = matrix.front().size();
        std::vector<int> dest;
        int rowLeftBottomStart = 0;
        int columnLeftBottomStart = 0;
        int rowTopRightStart = 0;
        int columnTopRightStart = 0;
        int rowDelta = -1;
        int columnDelta = 1;
        for (int index = 0; index < rowCount + columnCount - 1; ++index)
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
    void processDiagonal(std::vector<std::vector<int>> const &matrix, int row, int column, int rowDelta, int columnDelta, std::vector<int> &dest) const
    {
        const int rowCount = matrix.size();
        const int columnCount = matrix.front().size();
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