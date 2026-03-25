#include <cstdint>
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
        if ((totalSum % 2) == 1)
            return false;
        const int64_t halfSum = totalSum / 2;
        int64_t rowSum = 0;
        for (size_t row = 0; (row < rowCount) && (rowSum < halfSum); ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                rowSum += grid[row][column];
            if (rowSum == halfSum)
                return true;
        }
        int64_t columnSum = 0;
        for (size_t column = 0; (column < columnCount) && (columnSum < halfSum); ++column)
        {
            for (size_t row = 0; row < rowCount; ++row)
                columnSum += grid[row][column];
            if (columnSum == halfSum)
                return true;
        }
        return false;
    }
};

}

namespace EqualSumGridPartition1Task
{

TEST(EqualSumGridPartition1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canPartitionGrid({{1, 4}, {2, 3}}));
    ASSERT_EQ(false, solution.canPartitionGrid({{1, 3}, {2, 4}}));
}

TEST(EqualSumGridPartition1TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.canPartitionGrid({{1, 2}, {2, 2}}));
}

}
