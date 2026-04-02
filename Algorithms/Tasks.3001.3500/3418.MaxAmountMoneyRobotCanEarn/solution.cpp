#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumAmount(std::vector<std::vector<int>> const &coins) const
    {
        constexpr size_t maxNeutralize = 2;
        constexpr int unusedValue = INT_MIN;
        using DPPortion = std::vector<std::vector<int>>;
        using DPData = std::vector<DPPortion>;
        const size_t rowCount = coins.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = coins.front().size();
        const size_t columnMax = columnCount - 1;
        DPData dp(rowCount, DPPortion(columnCount, std::vector<int>(maxNeutralize + 1, unusedValue)));
        dp[0][0][0] = coins[0][0];
        if (coins[0][0] < 0)
            dp[0][0][1] = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (row < rowMax)
                {
                    dp[row + 1][column][0] = std::max(dp[row + 1][column][0], dp[row][column][0] + coins[row + 1][column]);
                    if (dp[row][column][1] != unusedValue)
                        dp[row + 1][column][1] = std::max(dp[row + 1][column][1], dp[row][column][1] + coins[row + 1][column]);
                    if (dp[row][column][2] != unusedValue)
                        dp[row + 1][column][2] = std::max(dp[row + 1][column][2], dp[row][column][2] + coins[row + 1][column]);
                    if (coins[row + 1][column] < 0)
                    {
                        dp[row + 1][column][1] = std::max(dp[row + 1][column][1], dp[row][column][0]);
                        if (dp[row][column][1] != unusedValue)
                            dp[row + 1][column][2] = std::max(dp[row + 1][column][2], dp[row][column][1]);
                    }
                }
                if (column < columnMax)
                {
                    dp[row][column + 1][0] = std::max(dp[row][column + 1][0], dp[row][column][0] + coins[row][column + 1]);
                    if (dp[row][column][1] != unusedValue)
                        dp[row][column + 1][1] = std::max(dp[row][column + 1][1], dp[row][column][1] + coins[row][column + 1]);
                    if (dp[row][column][2] != unusedValue)
                        dp[row][column + 1][2] = std::max(dp[row][column + 1][2], dp[row][column][2] + coins[row][column + 1]);
                    if (coins[row][column + 1] < 0)
                    {
                        dp[row][column + 1][1] = std::max(dp[row][column + 1][1], dp[row][column][0]);
                        if (dp[row][column][1] != unusedValue)
                            dp[row][column + 1][2] = std::max(dp[row][column + 1][2], dp[row][column][1]);
                    }
                }
            }
        }
        return std::max(dp.back().back()[0], std::max(dp.back().back()[1], dp.back().back()[2]));
    }
};

}

namespace MaxAmountMoneyRobotCanEarnTask
{

TEST(MaxAmountMoneyRobotCanEarnTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.maximumAmount({{0, 1, -1}, {1, -2, 3}, {2, -3, 4}}));
    ASSERT_EQ(40, solution.maximumAmount({{10, 10, 10}, {10, 10, 10}}));
}

}