#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxMoves(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<int>> dp(rowCount, std::vector<int>(columnCount, 0));
        int result = 0;
        for(size_t column = 0; column < columnCount - 1; ++column)
        {
            for (size_t row = 0; row < rowCount; ++row)
            {
                if ((column > 0) && (dp[row][column] == 0))
                    continue;
                if ((row > 0) && (grid[row][column] < grid[row - 1][column + 1]))
                {
                    dp[row - 1][column + 1] = std::max(dp[row - 1][column + 1], dp[row][column] + 1);
                    result = std::max(result, dp[row - 1][column + 1]);
                }
                if ((grid[row][column] < grid[row][column + 1]))
                {
                    dp[row][column + 1] = std::max(dp[row][column + 1], dp[row][column] + 1);
                    result = std::max(result, dp[row][column + 1]);
                }
                if ((row < rowMax) && (grid[row][column] < grid[row + 1][column + 1]))
                {
                    dp[row + 1][column + 1] = std::max(dp[row + 1][column + 1], dp[row][column] + 1);
                    result = std::max(result, dp[row + 1][column + 1]);
                }
            }
        }
        return result;
    }
};

}

namespace MaxNumberOfMovesInGridTask
{

TEST(MaxNumberOfMovesInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxMoves({{2, 4, 3, 5}, {5, 4, 9, 3}, {3, 4, 2, 11}, {10, 9, 13, 15}}));
    ASSERT_EQ(0, solution.maxMoves({{3, 2, 4}, {2, 1, 9}, {1, 1, 7}}));
}

}