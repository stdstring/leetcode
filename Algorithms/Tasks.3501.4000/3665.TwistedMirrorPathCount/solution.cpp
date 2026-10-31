#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int uniquePaths(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<int>> dp(rowCount, std::vector<int>(columnCount, 0));
        dp[0][0] = 1;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (dp[row][column] == 0)
                    continue;
                processMove(grid, dp, row, column, Direction::Right);
                processMove(grid, dp, row, column, Direction::Bottom);
            }
        }
        return dp.back().back();
    }

private:
    static constexpr int modValue = 1000000007;

    enum class Direction {Right, Bottom};

    void processMove(std::vector<std::vector<int>> const &grid, std::vector<std::vector<int>> &dp, size_t row, size_t column, Direction direction) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        if ((column == columnMax) && (direction == Direction::Right))
            return;
        if ((row == rowMax) && (direction == Direction::Bottom))
            return;
        const int value = dp[row][column];
        row += (direction == Direction::Bottom ? 1 : 0);
        column += (direction == Direction::Right ? 1 : 0);
        while ((row <= rowMax) && (column <= columnMax))
        {
            if (grid[row][column] == 0)
            {
                dp[row][column] = (dp[row][column] + value) % modValue;
                break;
            }
            direction = (direction == Direction::Right ? Direction::Bottom : Direction::Right);
            row += (direction == Direction::Bottom ? 1 : 0);
            column += (direction == Direction::Right ? 1 : 0);
        }
    }
};

}

namespace TwistedMirrorPathCountTask
{

TEST(TwistedMirrorPathCountTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.uniquePaths({{0, 1, 0}, {0, 0, 1}, {1, 0, 0}}));
    ASSERT_EQ(2, solution.uniquePaths({{0, 0}, {0, 0}}));
    ASSERT_EQ(1, solution.uniquePaths({{0, 1, 1}, {1, 1, 0}}));
}

}
