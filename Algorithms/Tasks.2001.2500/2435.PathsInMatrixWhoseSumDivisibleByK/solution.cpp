#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfPaths(std::vector<std::vector<int>> const &grid, int k) const
    {
        constexpr int modValue = 1000000007;
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<std::vector<int>>> dp(rowCount, std::vector<std::vector<int>>(columnCount, std::vector<int>(k, 0)));
        dp[0][0][grid[0][0] % k] = 1;
        for (size_t index = 0; index < rowCount + columnCount; ++index)
        {
            const size_t startRow = index < rowCount ? index : rowCount - 1;
            const size_t startColumn = index < rowCount ? 0 : index - startRow;
            const size_t size = std::min(startRow + 1, columnCount - startColumn);
            for (size_t shift = 0; shift < size; ++shift)
            {
                const size_t currentRow = startRow - shift;
                const size_t currentColumn = startColumn + shift;
                for (int rest = 0; rest < k; ++rest)
                {
                    if (currentRow < rowMax)
                    {
                        const int nextRest = (grid[currentRow + 1][currentColumn] + rest) % k;
                        dp[currentRow + 1][currentColumn][nextRest] = (dp[currentRow + 1][currentColumn][nextRest] + dp[currentRow][currentColumn][rest]) % modValue;
                    }
                    if (currentColumn < columnMax)
                    {
                        const int nextRest = (grid[currentRow][currentColumn + 1] + rest) % k;
                        dp[currentRow][currentColumn + 1][nextRest] = (dp[currentRow][currentColumn + 1][nextRest] + dp[currentRow][currentColumn][rest]) % modValue;
                    }
                }
            }
        }
        return dp.back().back()[0];
    }
};

}

namespace PathsInMatrixWhoseSumDivisibleByKTask
{

TEST(PathsInMatrixWhoseSumDivisibleByKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.numberOfPaths({{5, 2, 4}, {3, 0, 5}, {0, 7, 2}}, 3));
    ASSERT_EQ(1, solution.numberOfPaths({{0, 0}}, 5));
    ASSERT_EQ(10, solution.numberOfPaths({{7, 3, 4, 9}, {2, 3, 6, 2}, {2, 3, 7, 0}}, 1));
}

TEST(PathsInMatrixWhoseSumDivisibleByKTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numberOfPaths({{1, 5, 3, 7, 3, 2, 3, 5}}, 29));
}

}