#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> matrixBlockSum(std::vector<std::vector<int>> const &mat, int k) const
    {
        const size_t rowCount = mat.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = mat.front().size();
        const size_t columnMax = columnCount - 1;
        const size_t delta = k;
        std::vector<std::vector<int>> prefixSums(rowCount, std::vector<int>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                prefixSums[row][column] = mat[row][column];
                prefixSums[row][column] += (column > 0 ? prefixSums[row][column - 1] : 0);
                prefixSums[row][column] += (row > 0 ? prefixSums[row - 1][column] : 0);
                prefixSums[row][column] -= ((row > 0) && (column > 0) ? prefixSums[row - 1][column - 1] : 0);
            }
        }
        std::vector<std::vector<int>> result(rowCount, std::vector<int>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            const size_t rowTop = delta > row ? 0 : row - delta;
            const size_t rowBottom = row + delta > rowMax ? rowMax : row + delta;
            for (size_t column = 0; column < columnCount; ++column)
            {
                const size_t columnLeft = delta > column ? 0 : column - delta;
                const size_t columnRight = column + delta > columnMax ? columnMax : column + delta;
                result[row][column] = prefixSums[rowBottom][columnRight];
                result[row][column] -= (columnLeft > 0 ? prefixSums[rowBottom][columnLeft - 1] : 0);
                result[row][column] -= (rowTop > 0 ? prefixSums[rowTop - 1][columnRight] : 0);
                result[row][column] += ((columnLeft > 0) && (rowTop > 0) ? prefixSums[rowTop - 1][columnLeft - 1] : 0);
            }
        }
        return result;
    }
};

}

namespace MatrixBlockSumTask
{

TEST(MatrixBlockSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{12, 21, 16}, {27, 45, 33}, {24, 39, 28}}), solution.matrixBlockSum({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 1));
    ASSERT_EQ(std::vector<std::vector<int>>({{45, 45, 45}, {45, 45, 45}, {45, 45, 45}}), solution.matrixBlockSum({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 2));
}

}