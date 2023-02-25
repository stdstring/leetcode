#include <vector>

#include "gtest/gtest.h"

namespace
{

class NumMatrix
{
public:
    NumMatrix(std::vector<std::vector<int>> const &matrix)
    {
        for (size_t row = 0; row < matrix.size(); ++row)
        {
            int rowSum = 0;
            for (size_t column = 0; column < matrix.front().size(); ++column)
            {
                rowSum += matrix[row][column];
                if (column == 0)
                    _prefixSums.emplace_back();
                _prefixSums.back().push_back(rowSum + (row > 0 ? _prefixSums[row - 1][column] : 0));
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        const int sumA = (row1 > 0) && (col1 > 0) ? _prefixSums[row1 - 1][col1 - 1] : 0;
        const int sumB = (row1 > 0) ? _prefixSums[row1 - 1][col2] : 0;
        const int sumC = (col1 > 0) ? _prefixSums[row2][col1 - 1] : 0;
        const int sumD = _prefixSums[row2][col2];
        return sumD - sumC - sumB + sumA;
    }

private:
    std::vector<std::vector<int>> _prefixSums;
};

}

namespace RangeSumQuery2DImmutableTask
{

TEST(RangeSumQuery2DImmutableTaskTests, Examples)
{
    NumMatrix numMatrix({{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}});
    ASSERT_EQ(8, numMatrix.sumRegion(2, 1, 4, 3));
    ASSERT_EQ(11, numMatrix.sumRegion(1, 1, 2, 2));
    ASSERT_EQ(12, numMatrix.sumRegion(1, 2, 2, 4));
}

}