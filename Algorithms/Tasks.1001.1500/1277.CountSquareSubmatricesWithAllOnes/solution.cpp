#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countSquares(std::vector<std::vector<int>> const &matrix) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::vector<std::vector<int>> dp(rowCount, std::vector<int>(columnCount, 0));
        int result = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (matrix[row][column] == 0)
                    continue;
                int minSize = std::min(INT_MAX, row > 0 ? dp[row - 1][column] : 0);
                minSize = std::min(minSize, column > 0 ? dp[row][column - 1] : 0);
                minSize = std::min(minSize, (row > 0) && (column > 0) ? dp[row - 1][column - 1] : 0);
                dp[row][column] = minSize + 1;
                result += dp[row][column];
            }
        }
        return result;
    }
};

}

namespace CountSquareSubmatricesWithAllOnesTask
{

TEST(CountSquareSubmatricesWithAllOnesTaskTests, Examples2)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.countSquares({{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}}));
    ASSERT_EQ(7, solution.countSquares({{1, 0, 1}, {1, 1, 0}, {1, 1, 0}}));
}

}