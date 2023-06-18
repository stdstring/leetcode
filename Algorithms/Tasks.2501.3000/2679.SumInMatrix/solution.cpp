#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int matrixSum(std::vector<std::vector<int>> const &nums) const
    {
        std::vector<std::vector<int>> matrix(nums);
        for (std::vector<int> &row : matrix)
            std::sort(row.begin(), row.end(), std::greater<int>());
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        int result = 0;
        for (size_t column = 0; column < columnCount; ++column)
        {
            int bestValue = 0;
            for (size_t row = 0; row < rowCount; ++row)
                bestValue = std::max(bestValue, matrix[row][column]);
            result += bestValue;
        }
        return result;
    }
};

}

namespace SumInMatrixTask
{

TEST(SumInMatrixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.matrixSum({{7, 2, 1}, {6, 4, 2}, {6, 5, 3}, {3, 2, 1}}));
    ASSERT_EQ(1, solution.matrixSum({{1}}));
}

}