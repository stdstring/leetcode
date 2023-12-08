#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSwaps(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        std::vector<size_t> rows(rowCount, 0);
        for (size_t row = 0; row < rowCount; ++row)
            rows[row] = calcRowContinuousZeroFromRight(grid[row]);
        size_t swapCount = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            const size_t expectedRowValue = rows.size() - 1 - row;
            if (rows[row] >= expectedRowValue)
                continue;
            const size_t nearestRow = findNearestRow(rows, row, expectedRowValue);
            if (nearestRow == rows.size())
                return -1;
            moveUp(rows, nearestRow, row);
            swapCount += (nearestRow - row);
        }
        return static_cast<int>(swapCount);
    }

private:
    [[nodiscard]] size_t calcRowContinuousZeroFromRight(std::vector<int> const &row) const
    {
        size_t result = 0;
        for (auto iterator = row.crbegin(); iterator != row.crend(); ++iterator)
        {
            if (*iterator != 0)
                break;
            ++result;
        }
        return result;
    }

    [[nodiscard]] size_t findNearestRow(std::vector<size_t> const &rows, size_t start, size_t minValue) const
    {
        for (size_t row = start; row < rows.size(); ++row)
        {
            if (rows[row] >= minValue)
                return row;
        }
        return rows.size();
    }

    void moveUp(std::vector<size_t> &rows, size_t source, size_t dest) const
    {
        for (size_t row = source; row != dest; --row)
            std::swap(rows[row], rows[row - 1]);
    }
};

}

namespace MinSwaps2ArrangeBinaryGridTask
{

TEST(MinSwaps2ArrangeBinaryGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minSwaps({{0, 0, 1}, {1, 1, 0}, {1, 0, 0}}));
    ASSERT_EQ(-1, solution.minSwaps({{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}}));
    ASSERT_EQ(0, solution.minSwaps({{1, 0, 0}, {1, 1, 0}, {1, 1, 1}}));
}

TEST(MinSwaps2ArrangeBinaryGridTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minSwaps({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}));
}

}