#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> minAbsDiff(std::vector<std::vector<int>> const &grid, int k) const
    {
        const size_t submatrixSide = k;
        const size_t submatrixSize = submatrixSide * submatrixSide;
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t resultRowCount = rowCount - k + 1;
        const size_t resultColumnCount = columnCount - k + 1;
        std::vector<std::vector<int>> result(resultRowCount, std::vector<int>(resultColumnCount, 0));
        if (k == 1)
            return result;
        for (size_t startRow = 0; startRow < resultRowCount; ++startRow)
        {
            for (size_t startColumn = 0; startColumn < resultColumnCount; ++startColumn)
            {
                std::vector<int> values(submatrixSize, 0);
                for (size_t row = 0; row < submatrixSide; ++row)
                {
                    for (size_t column = 0; column < submatrixSide; ++column)
                    {
                        values[row * submatrixSide + column] = grid[startRow + row][startColumn + column];
                    }
                }
                std::ranges::sort(values);
                int minDiff = INT_MAX;
                for (size_t index = 1; index < values.size(); ++index)
                {
                    if (values[index] > values[index - 1])
                        minDiff = std::min(minDiff, values[index] - values[index - 1]);
                }
                result[startRow][startColumn] = minDiff == INT_MAX ? 0 : minDiff;
            }
        }
        return result;
    }
};

}

namespace MinAbsoluteDiffSlidingSubmatrixTask
{

TEST(MinAbsoluteDiffSlidingSubmatrixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{2}}), solution.minAbsDiff({{1, 8}, {3, -2}}, 2));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0}}), solution.minAbsDiff({{3, -1}}, 1));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2}}), solution.minAbsDiff({{1, -2, 3}, {2, 3, 5}}, 2));
}

}