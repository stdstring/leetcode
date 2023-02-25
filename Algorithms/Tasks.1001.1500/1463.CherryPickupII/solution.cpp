#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int cherryPickup(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<std::vector<size_t>>> dp(rowCount, std::vector<std::vector<size_t>>(columnCount, std::vector<size_t>(columnCount, 0)));
        dp[0][0][columnCount - 1] = static_cast<size_t>(grid[0][0]) + static_cast<size_t>(grid[0][columnCount - 1]);
        const size_t initValue = dp[0][0][columnCount - 1] == 0 ? 1 : 0;
        dp[0][0][columnCount - 1] += initValue;
        for (size_t row = 0; row < rowCount - 1; ++row)
        {
            for (size_t firstIndex = 0; firstIndex < columnCount; ++firstIndex)
            {
                for (size_t secondIndex = 0; secondIndex < columnCount; ++secondIndex)
                {
                    const size_t prevValue = dp[row][firstIndex][secondIndex];
                    if (prevValue == 0)
                        continue;
                    if (firstIndex > 0)
                        processSecondRobotMoves(row, firstIndex - 1, secondIndex, prevValue, grid, dp);
                    processSecondRobotMoves(row, firstIndex, secondIndex, prevValue, grid, dp);
                    if (firstIndex < columnCount - 1)
                        processSecondRobotMoves(row, firstIndex + 1, secondIndex, prevValue, grid, dp);
                }
            }
        }
        size_t maxCherriesCount = 0;
        for (size_t firstIndex = 0; firstIndex < columnCount; ++firstIndex)
        {
            for (size_t secondIndex = 0; secondIndex < columnCount; ++secondIndex)
               maxCherriesCount = std::max(maxCherriesCount, dp[rowCount - 1][firstIndex][secondIndex] - initValue);
        }
        return static_cast<int>(maxCherriesCount);
    }

private:
    void processSecondRobotMoves(size_t row, size_t firstIndex, size_t secondIndex, size_t prevValue, std::vector<std::vector<int>> const &grid, std::vector<std::vector<std::vector<size_t>>> &dp) const
    {
        const size_t columnCount = grid.front().size();
        std::vector<size_t> &dpSecond(dp[row + 1][firstIndex]);
        if (secondIndex > 0)
            dpSecond[secondIndex - 1] = std::max(dpSecond[secondIndex - 1], prevValue + grid[row + 1][firstIndex] + (firstIndex == secondIndex - 1 ? 0 : grid[row + 1][secondIndex - 1]));
        dpSecond[secondIndex] = std::max(dpSecond[secondIndex], prevValue + grid[row + 1][firstIndex] + (firstIndex == secondIndex ? 0 : grid[row + 1][secondIndex]));
        if (secondIndex < columnCount - 1)
            dpSecond[secondIndex + 1] = std::max(dpSecond[secondIndex + 1], prevValue + grid[row + 1][firstIndex] + (firstIndex == secondIndex + 1 ? 0 : grid[row + 1][secondIndex + 1]));
    }
};

}

namespace CherryPickupIITask
{

TEST(CherryPickupIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(24, solution.cherryPickup({{3, 1, 1}, {2, 5, 1}, {1, 5, 5}, {2, 1, 1}}));
    ASSERT_EQ(28, solution.cherryPickup({{1, 0, 0, 0, 0, 0, 1},
                                         {2, 0, 0, 0, 0, 3, 0},
                                         {2, 0, 9, 0, 0, 0, 0},
                                         {0, 3, 0, 5, 4, 0, 0},
                                         {1, 0, 2, 3, 0, 0, 6}}));
}

TEST(CherryPickupIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(96, solution.cherryPickup({{0, 0, 10, 2, 8, 4, 0},
                                         {7, 9, 3, 5, 4, 8, 3},
                                         {6, 9, 8, 3, 5, 6, 0},
                                         {0, 4, 1, 1, 9, 3, 7},
                                         {5, 6, 9, 8, 8, 10, 10},
                                         {9, 2, 9, 7, 4, 8, 3},
                                         {1, 6, 1, 2, 0, 9, 9}}));
    ASSERT_EQ(96, solution.cherryPickup({{0, 8, 7, 10, 9, 10, 0, 9, 6},
                                         {8, 7, 10, 8, 7, 4, 9, 6, 10},
                                         {8, 1, 1, 5, 1, 5, 5, 1, 2},
                                         {9, 4, 10, 8, 8, 1, 9, 5, 0},
                                         {4, 3, 6, 10, 9, 2, 4, 8, 10},
                                         {7, 3, 2, 8, 3, 3, 5, 9, 8},
                                         {1, 2, 6, 5, 6, 2, 0, 10, 0}}));
}

}