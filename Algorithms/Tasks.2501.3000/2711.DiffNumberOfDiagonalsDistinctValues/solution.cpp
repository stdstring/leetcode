#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> differenceOfDistinctValues(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<int>> result(rowCount, std::vector<int>(columnCount, 0));
        for (size_t column = 0; column < columnCount; ++column)
            processDiagonal(grid, 0, column, result);
        for (size_t row = 1; row < rowCount; ++row)
            processDiagonal(grid, row, 0, result);
        return result;
    }

private:
    void processDiagonal(std::vector<std::vector<int>> const &grid, size_t startRow, size_t startColumn, std::vector<std::vector<int>> &result) const
    {
        constexpr int maxValue = 50;
        std::vector<int> bottomRightNumbers(maxValue + 1, 0);
        std::vector<int> topLeftNumbers(maxValue + 1, 0);
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        for (size_t row = startRow, column = startColumn; (row < rowCount) && (column < columnCount); ++row, ++column)
            ++bottomRightNumbers[grid[row][column]];
        for (size_t row = startRow, column = startColumn; (row < rowCount) && (column < columnCount); ++row, ++column)
        {
            --bottomRightNumbers[grid[row][column]];
            auto accFun = [](int acc, int value) { return acc + (value > 0 ? 1 : 0); };
            const int bottomRightValue = std::accumulate(bottomRightNumbers.cbegin(), bottomRightNumbers.cend(), 0, accFun);
            const int topLeftValue = std::accumulate(topLeftNumbers.cbegin(), topLeftNumbers.cend(), 0, accFun);
            result[row][column] = std::abs(topLeftValue - bottomRightValue);
            ++topLeftNumbers[grid[row][column]];
        }
    }
};

}

namespace DiffNumberOfDiagonalsDistinctValuesTask
{

TEST(DiffNumberOfDiagonalsDistinctValuesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1, 0}, {1, 0, 1}, {0, 1, 1}}),
              solution.differenceOfDistinctValues({{1, 2, 3}, {3, 1, 5}, {3, 2, 1}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0}}), solution.differenceOfDistinctValues({{1}}));
}

}