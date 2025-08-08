#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxCollectedFruits(std::vector<std::vector<int>> const &fruits) const
    {
        // child1
        int child1Result = calcMatrixSpur(fruits);
        // child2
        int child2Result = processChild2(fruits);
        // child3
        int child3Result = processChild3(fruits);
        return child1Result + child2Result + child3Result - 2 * fruits.back().back();
    }

private:
    [[nodiscard]] int calcMatrixSpur(std::vector<std::vector<int>> const &source) const
    {
        int result = 0;
        for (size_t index = 0; index < source.size(); ++index)
            result += source[index][index];
        return result;
    }

    [[nodiscard]] int processChild2(std::vector<std::vector<int>> const &fruits) const
    {
        const size_t n = fruits.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
        dp[0][n - 1] = fruits[0][n - 1];
        for (size_t row = 0; row < n - 1; ++row)
        {
            for (size_t column = std::max(row + 1, n - 1 - row); column < n; ++column)
            {
                if ((column - 1) > row)
                    dp[row + 1][column - 1] = std::max(dp[row + 1][column - 1], dp[row][column] + fruits[row + 1][column - 1]);
                dp[row + 1][column] = std::max(dp[row + 1][column], dp[row][column] + fruits[row + 1][column]);
                if (column < (n - 1))
                    dp[row + 1][column + 1] = std::max(dp[row + 1][column + 1], dp[row][column] + fruits[row + 1][column + 1]);
            }
        }
        return dp[n - 1][n - 1];
    }

    [[nodiscard]] int processChild3(std::vector<std::vector<int>> const &fruits) const
    {
        const size_t n = fruits.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
        dp[n - 1][0] = fruits[n - 1][0];
        for (size_t column = 0; column < n - 1; ++ column)
        {
            for (size_t row = std::max(column + 1, n - 1 - column); row < n; ++row)
            {
                if ((row - 1) > column)
                    dp[row - 1][column + 1] = std::max(dp[row - 1][column + 1], dp[row][column] + fruits[row - 1][column + 1]);
                dp[row][column + 1] = std::max(dp[row][column + 1], dp[row][column] + fruits[row][column + 1]);
                if (row < (n - 1))
                    dp[row + 1][column + 1] = std::max(dp[row + 1][column + 1], dp[row][column] + fruits[row + 1][column + 1]);
            }
        }
        return dp[n - 1][n - 1];
    }
};

}

namespace FindMaxNumberFruitsCollectedTask
{

TEST(FindMaxNumberFruitsCollectedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(100, solution.maxCollectedFruits({{1, 2, 3, 4}, {5, 6, 8, 7}, {9, 10, 11, 12}, {13, 14, 15, 16}}));
    ASSERT_EQ(4, solution.maxCollectedFruits({{1, 1}, {1, 1}}));
}

TEST(FindMaxNumberFruitsCollectedTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(145, solution.maxCollectedFruits({{8, 5, 0, 17, 15}, {6, 0, 15, 6, 0}, {7, 19, 16, 8, 18}, {11, 3, 2, 12, 13}, {17, 15, 15, 4, 6}}));
}

}