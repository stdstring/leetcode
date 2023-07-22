#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double knightProbability(int n, int k, int row, int column) const
    {
        std::vector<double> dp(1LL * n * n, 0.0);
        dp[n * row + column] = 1.0;
        for (int step = 0; step < k; ++step)
        {
            std::vector<double> nextDp(1LL * n * n, 0);
            for (int currentRow = 0; currentRow < n; ++currentRow)
            {
                for (int currentColumn = 0; currentColumn < n; ++currentColumn)
                {
                    // top (-2) - left (-1)
                    if ((currentRow > 1) && (currentColumn > 0))
                        nextDp[(currentRow - 2) * n + (currentColumn - 1)] += (dp[currentRow * n + currentColumn] / 8.0);
                    // top (-2) - right (+1)
                    if ((currentRow > 1) && (currentColumn < (n - 1)))
                        nextDp[(currentRow - 2) * n + (currentColumn + 1)] += (dp[currentRow * n + currentColumn] / 8.0);
                    // left (-2) - top (-1)
                    if ((currentRow > 0) && (currentColumn > 1))
                        nextDp[(currentRow - 1) * n + (currentColumn - 2)] += (dp[currentRow * n + currentColumn] / 8.0);
                    // left (-2) - bottom (+1)
                    if ((currentRow < (n - 1)) && (currentColumn > 1))
                        nextDp[(currentRow + 1) * n + (currentColumn - 2)] += (dp[currentRow * n + currentColumn] / 8.0);
                    // bottom (+2) - left (-1)
                    if ((currentRow < (n - 2)) && (currentColumn > 0))
                        nextDp[(currentRow + 2) * n + (currentColumn - 1)] += (dp[currentRow * n + currentColumn] / 8.0);
                    // bottom (+2) - right (+1)
                    if ((currentRow < (n - 2)) && (currentColumn < (n - 1)))
                        nextDp[(currentRow + 2) * n + (currentColumn + 1)] += (dp[currentRow * n + currentColumn] / 8.0);
                    // right (+2) - top (-1)
                    if ((currentRow > 0) && (currentColumn < (n - 2)))
                        nextDp[(currentRow - 1) * n + (currentColumn + 2)] += (dp[currentRow * n + currentColumn] / 8.0);
                    // right (+2) - bottom (+1)
                    if ((currentRow < (n - 1)) && (currentColumn < (n - 2)))
                        nextDp[(currentRow + 1) * n + (currentColumn + 2)] += (dp[currentRow * n + currentColumn] / 8.0);
                }
            }
            std::swap(dp, nextDp);
        }
        return std::accumulate(dp.cbegin(), dp.cend(), 0.0);
    }
};

}

namespace KnightProbabilityInChessboardTask
{

TEST(KnightProbabilityInChessboardTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_NEAR(0.06250, solution.knightProbability(3, 2, 0, 0), 0.00001);
    ASSERT_NEAR(1.00000, solution.knightProbability(1, 0, 0, 0), 0.00001);
}

TEST(KnightProbabilityInChessboardTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_NEAR(0.03906, solution.knightProbability(4, 3, 0, 0), 0.00001);
    ASSERT_NEAR(1.00000, solution.knightProbability(2, 0, 0, 0), 0.00001);
    ASSERT_NEAR(0.00000, solution.knightProbability(2, 1, 0, 0), 0.00001);
}

TEST(KnightProbabilityInChessboardTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_NEAR(0.00000, solution.knightProbability(3, 2, 1, 1), 0.00001);
    ASSERT_NEAR(0.00019, solution.knightProbability(8, 30, 6, 4), 0.00001);
}

}