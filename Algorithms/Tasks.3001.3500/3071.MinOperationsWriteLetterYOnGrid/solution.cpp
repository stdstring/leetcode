#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumOperationsToWriteY(std::vector<std::vector<int>> const &grid) const
    {
        constexpr size_t valuesCount = 3;
        const size_t n = grid.size();
        std::vector<size_t> yValues(valuesCount, 0);
        std::vector<size_t> backgroundValues(valuesCount, 0);
        for (size_t row = 0, leftYColumn = 0, rightYColumn = n - 1; row < n; ++row)
        {
            for (size_t column = 0; column < n; ++column)
            {
                if ((column != leftYColumn) && (column != rightYColumn))
                    ++backgroundValues[grid[row][column]];
            }
            ++yValues[grid[row][leftYColumn]];
            if (leftYColumn != rightYColumn)
                ++yValues[grid[row][rightYColumn]];
            if (leftYColumn < rightYColumn)
            {
                ++leftYColumn;
                --rightYColumn;
            }
        }
        const size_t totalYCount = std::accumulate(yValues.cbegin(), yValues.cend(), 0ULL);
        const size_t totalBackgroundCount = std::accumulate(backgroundValues.cbegin(), backgroundValues.cend(), 0ULL);
        size_t minOperationsCount = n * n;
        for (size_t yValue = 0; yValue < valuesCount; ++yValue)
        {
            for (size_t backgroundValue = 0; backgroundValue < valuesCount; ++backgroundValue)
            {
                if (yValue == backgroundValue)
                    continue;
                size_t currentOperationCount = (totalYCount - yValues[yValue]) + (totalBackgroundCount - backgroundValues[backgroundValue]);
                minOperationsCount = std::min(minOperationsCount, currentOperationCount);
            }
        }
        return static_cast<int>(minOperationsCount);
    }
};

}

namespace MinOperationsWriteLetterYOnGridTask
{

TEST(MinOperationsWriteLetterYOnGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumOperationsToWriteY({{1, 2, 2}, {1, 1, 0}, {0, 1, 0}}));
    ASSERT_EQ(12, solution.minimumOperationsToWriteY({{0, 1, 0, 1, 0}, {2, 1, 0, 1, 2}, {2, 2, 2, 0, 1}, {2, 2, 2, 2, 2}, {2, 1, 2, 2, 2}}));
}

}