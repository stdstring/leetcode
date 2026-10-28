#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minCost(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        const int valuesCount = 1024;
        const int maxValue = valuesCount - 1;
        std::vector<std::vector<std::vector<bool>>> dp(rowCount, std::vector<std::vector<bool>>(columnCount, std::vector<bool>(valuesCount, false)));
        dp[0][0][grid[0][0]] = true;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                for (int value = 0; value < valuesCount; ++value)
                {
                    if (!dp[row][column][value])
                        continue;
                    if (row < rowMax)
                        dp[row + 1][column][value ^ grid[row + 1][column]] = true;
                    if (column < columnMax)
                        dp[row][column + 1][value ^ grid[row][column + 1]] = true;
                }
            }
        }
        for (int value = 0; value < valuesCount; ++value)
        {
            if (dp.back().back()[value])
                return value;
        }
        return maxValue;
    }
};

}

namespace MinXORPathInGridTask
{

TEST(MinXORPathInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.minCost({{1, 2}, {3, 4}}));
    ASSERT_EQ(9, solution.minCost({{6, 7}, {5, 8}}));
    ASSERT_EQ(0, solution.minCost({{2, 7, 5}}));
}

}