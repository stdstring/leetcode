#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxPathScore(std::vector<std::vector<int>> const &grid, int k) const
    {
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<std::vector<int>>> dp(rowCount, std::vector<std::vector<int>>(columnCount, std::vector<int>(k + 1, -1)));
        dp[0][0][calcCost(grid[0][0])] = grid[0][0];
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                for (int cost = 0; cost <= k; ++cost)
                {
                    if (dp[row][column][cost] == -1)
                        continue;
                    if (row < rowMax)
                    {
                        const int nextCost = cost + calcCost(grid[row + 1][column]);
                        if (nextCost <= k)
                            dp[row + 1][column][nextCost] = std::max(dp[row + 1][column][nextCost], dp[row][column][cost] + grid[row + 1][column]);
                    }
                    if (column < columnMax)
                    {
                        const int nextCost = cost + calcCost(grid[row][column + 1]);
                        if (nextCost <= k)
                            dp[row][column + 1][nextCost] = std::max(dp[row][column + 1][nextCost], dp[row][column][cost] + grid[row][column + 1]);
                    }
                }
            }
        }
        int result = -1;
        for (int value : dp[rowMax][columnMax])
            result = std::max(result, value);
        return result;
    }

private:
    [[nodiscard]] int calcCost(int value) const
    {
        return value == 0 ? 0 : 1;
    }
};

}


namespace MaxPathScoreInGridTask
{

TEST(MaxPathScoreInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxPathScore({{0, 1}, {2, 0}}, 1));
    ASSERT_EQ(-1, solution.maxPathScore({{0, 1}, {1, 2}}, 1));
}

}