#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSum(std::vector<std::vector<int>> const &grid) const
    {
        constexpr size_t hourglassSize = 3;
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t rowMax = rowCount - hourglassSize;
        const size_t columnMax = columnCount - hourglassSize;
        int bestSum = 0;
        for (size_t row = 0; row <= rowMax; ++row)
        {
            for (size_t column = 0; column <= columnMax; ++column)
            {
                int currentSum = grid[row][column] +
                                 grid[row][column + 1] +
                                 grid[row][column + 2] +
                                 grid[row + 1][column + 1] +
                                 grid[row + 2][column] +
                                 grid[row + 2][column + 1] +
                                 grid[row + 2][column + 2];
                bestSum = std::max(bestSum, currentSum);
            }
        }
        return bestSum;
    }
};

}

namespace MaxSumOfHourglassTask
{

TEST(MaxSumOfHourglassTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(30, solution.maxSum({{6, 2, 1, 3}, {4, 2, 1, 5}, {9, 2, 8, 7}, {4, 1, 2, 9}}));
    ASSERT_EQ(35, solution.maxSum({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
}

}