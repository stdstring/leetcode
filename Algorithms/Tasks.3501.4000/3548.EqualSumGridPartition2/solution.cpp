#include <cstdint>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canPartitionGrid(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        int64_t totalSum = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                totalSum += grid[row][column];
        }
        // row direct
        int64_t rowSum = 0;
        std::unordered_set<int64_t> numbers;
        for (size_t row = 0; row < rowCount - 1; ++row)
        {
            rowSum += calcRowSum(grid, row, numbers);
            if ((2 * rowSum) < totalSum)
                continue;
            if ((2 * rowSum) == totalSum)
                return true;
            int64_t delta = 2 * rowSum - totalSum;
            if ((row == 0) && ((grid[row][0] == delta) || (grid[row][columnCount - 1] == delta)))
                return true;
            if ((columnCount == 1) && ((grid[0][0] == delta) || (grid[row][0] == delta)))
                return true;
            if ((row > 0) && (columnCount > 1) && numbers.contains(delta))
                return true;
        }
        // row reverse
        rowSum = 0;
        numbers.clear();
        for (size_t rrow = 0; rrow < rowCount - 1; ++rrow)
        {
            const size_t row = rowCount - 1 - rrow;
            rowSum += calcRowSum(grid, row, numbers);
            if ((2 * rowSum) < totalSum)
                continue;
            if ((2 * rowSum) == totalSum)
                return true;
            int64_t delta = 2 * rowSum - totalSum;
            if ((rrow == 0) && ((grid[row][0] == delta) || (grid[row][columnCount - 1] == delta)))
                return true;
            if ((columnCount == 1) && ((grid[rowCount - 1][0] == delta) || (grid[row][0] == delta)))
                return true;
            if ((rrow > 0) && (columnCount > 1) && numbers.contains(delta))
                return true;
        }
        // column direct
        int64_t columnSum = 0;
        numbers.clear();
        for (size_t column = 0; column < columnCount - 1; ++column)
        {
            columnSum += calcColumnSum(grid, column, numbers);
            if ((2 * columnSum) < totalSum)
                continue;
            if ((2 * columnSum) == totalSum)
                return true;
            int64_t delta = 2 * columnSum - totalSum;
            if ((column == 0) && ((grid[0][column] == delta) || (grid[rowCount - 1][column] == delta)))
                return true;
            if ((rowCount == 1) && ((grid[0][0] == delta) || (grid[0][column] == delta)))
                return true;
            if ((column > 0) && (rowCount > 1) && numbers.contains(delta))
                return true;
        }
        // column reverse
        columnSum = 0;
        numbers.clear();
        for (size_t rcolumn = 0; rcolumn < columnCount - 1; ++rcolumn)
        {
            const size_t column = columnCount - 1 - rcolumn;
            columnSum += calcColumnSum(grid, column, numbers);
            if ((2 * columnSum) < totalSum)
                continue;
            if ((2 * columnSum) == totalSum)
                return true;
            int64_t delta = 2 * columnSum - totalSum;
            if ((rcolumn == 0) && ((grid[0][column] == delta) || (grid[rowCount - 1][column] == delta)))
                return true;
            if ((rowCount == 1) && ((grid[0][columnCount - 1] == delta) || (grid[0][column] == delta)))
                return true;
            if ((rcolumn > 0) && (rowCount > 1) && numbers.contains(delta))
                return true;
        }
        return false;
    }

private:
    [[nodiscard]] int64_t calcRowSum(std::vector<std::vector<int>> const &grid, size_t row, std::unordered_set<int64_t> &numbers) const
    {
        const size_t columnCount = grid.front().size();
        int64_t result = 0;
        for (size_t column = 0; column < columnCount; ++column)
        {
            result += grid[row][column];
            numbers.emplace(grid[row][column]);
        }
        return result;
    }

    [[nodiscard]] int64_t calcColumnSum(std::vector<std::vector<int>> const& grid, size_t column, std::unordered_set<int64_t> &numbers) const
    {
        const size_t rowCount = grid.size();
        int64_t result = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            result += grid[row][column];
            numbers.emplace(grid[row][column]);
        }
        return result;
    }
};

}

namespace EqualSumGridPartition2Task
{

TEST(EqualSumGridPartition2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canPartitionGrid({{1, 4}, {2, 3}}));
    ASSERT_EQ(true, solution.canPartitionGrid({{1, 2}, {3, 4}}));
    ASSERT_EQ(false, solution.canPartitionGrid({{1, 2, 4}, {2, 3, 5}}));
    ASSERT_EQ(false, solution.canPartitionGrid({{4, 1, 8}, {3, 2, 6}}));
}

TEST(EqualSumGridPartition2TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canPartitionGrid({{1, 4}, {2, 2}}));
}

TEST(EqualSumGridPartition2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canPartitionGrid({{253, 10, 10}}));
    ASSERT_EQ(false, solution.canPartitionGrid({{10, 5, 4, 5}}));
    ASSERT_EQ(true, solution.canPartitionGrid({{5, 5, 6, 2, 2, 2}}));
}

}
