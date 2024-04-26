#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minFallingPathSum(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        if (rowCount == 1)
            return *std::ranges::min_element(grid.front());
        if (columnCount == 1)
            return std::accumulate(grid.cbegin(), grid.cend(), 0, [](int acc, std::vector<int> const &row) {return acc + row[0];});
        std::vector<int> currentDp(grid[0]);
        for (size_t row = 1; row < rowCount; ++row)
        {
            std::pair<size_t, size_t> currentMin2Numbers(calcMin2Numbers(currentDp));
            std::vector<int> nextDp(columnCount, 0);
            for (size_t column = 0; column < columnCount; ++column)
                nextDp[column] = grid[row][column] + currentDp[(column == currentMin2Numbers.first) ? currentMin2Numbers.second : currentMin2Numbers.first];
            std::swap(currentDp, nextDp);
        }
        return *std::ranges::min_element(currentDp);
    }

private:
    [[nodiscard]] std::pair<size_t, size_t> calcMin2Numbers(std::vector<int> const &row, std::pair<size_t, size_t> const &prevValue, size_t index) const
    {
        if (row[prevValue.second] <= row[index])
            return prevValue;
        if (row[index] < row[prevValue.first])
            return std::pair<size_t, size_t>(index, prevValue.first);
        return std::pair<size_t, size_t>(prevValue.first, index);
    }

    [[nodiscard]] std::pair<size_t, size_t> calcMin2Numbers(std::vector<int> const &row) const
    {
        std::pair<size_t, size_t> result(row[0] <= row[1] ? 0 : 1, row[0] <= row[1] ? 1 : 0);
        for (size_t index = 2; index < row.size(); ++index)
            result = calcMin2Numbers(row, result, index);
        return result;
    }
};

}

namespace MinFallingPathSum2Task
{

TEST(MinFallingPathSum2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.minFallingPathSum({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    ASSERT_EQ(7, solution.minFallingPathSum({{7}}));
}

TEST(MinFallingPathSum2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(-192, solution.minFallingPathSum({{-73, 61, 43, -48, -36},
                                                {3, 30, 27, 57, 10},
                                                {96, -76, 84, 59, -15},
                                                {5, -49, 76, 31, -7},
                                                {97, 91, 61, -46, 67}}));
}

}