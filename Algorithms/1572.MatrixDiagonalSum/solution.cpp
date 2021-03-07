#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int diagonalSum(std::vector<std::vector<int>> const &mat) const
    {
        const size_t rowCount = mat.size();
        int sum = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            sum += mat[row][row];
            if (row != (rowCount - 1 - row))
                sum += mat[row][rowCount - 1 - row];
        }
        return sum;
    }
};

}

namespace MatrixDiagonalSumTask
{

TEST(MatrixDiagonalSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(25, solution.diagonalSum({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    ASSERT_EQ(8, solution.diagonalSum({{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}}));
    ASSERT_EQ(5, solution.diagonalSum({{5}}));
}

}