#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> pathsWithMaxScore(std::vector<std::string> const &board) const
    {
        const size_t rowCount = board.size();
        const size_t columnCount = board.front().size();
        std::vector<std::vector<TCellData>> dp(rowCount, std::vector<TCellData>(columnCount, TCellData(-1, -1)));
        dp.back().back() = TCellData(0, 1);
        for (size_t rowIndex = 0; rowIndex < rowCount; ++rowIndex)
        {
            const size_t row = rowCount - 1 - rowIndex;
            for (size_t columnIndex = 0; columnIndex < columnCount; ++columnIndex)
            {
                const size_t column = columnCount - 1 - columnIndex;
                if (row > 0)
                    updateDP(row - 1, column, dp[row][column], board, dp);
                if (column > 0)
                    updateDP(row, column - 1, dp[row][column], board, dp);
                if ((row > 0) && (column > 0))
                    updateDP(row - 1, column - 1, dp[row][column], board, dp);
            }
        }
        if (dp[0][0].second == -1)
            return {0, 0};
        return {dp[0][0].first, dp[0][0].second};
    }

private:
    // max sum, path count
    using TCellData = std::pair<int, int>;

    void updateDP(size_t nextRow,
                  size_t nextColumn,
                  TCellData const &currentDp,
                  std::vector<std::string> const &board,
                  std::vector<std::vector<TCellData>> &dp) const
    {
        constexpr int modValue = 1000000007;
        const char nextCell = board[nextRow][nextColumn];
        if (nextCell == 'X')
            return;
        const int nextSum = currentDp.first + (((nextRow == 0) && (nextColumn == 0)) ? 0 : nextCell - '0');
        if (nextSum < dp[nextRow][nextColumn].first)
            return;
        if (nextSum == dp[nextRow][nextColumn].first)
        {
            dp[nextRow][nextColumn].second = (dp[nextRow][nextColumn].second + currentDp.second) % modValue;
        }
        else
            dp[nextRow][nextColumn] = TCellData(nextSum, currentDp.second);
    }
};

}

namespace NumberOfPathsWithMaxScoreTask
{

TEST(NumberOfPathsWithMaxScoreTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({7, 1}), solution.pathsWithMaxScore({"E23", "2X2", "12S"}));
    ASSERT_EQ(std::vector<int>({4, 2}), solution.pathsWithMaxScore({"E12", "1X1", "21S"}));
    ASSERT_EQ(std::vector<int>({0, 0}), solution.pathsWithMaxScore({"E11", "XXX", "11S"}));
}

}
