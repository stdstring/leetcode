#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> largestLocal(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<int>> result(rowCount - 2, std::vector<int>(columnCount - 2, 0));
        for (size_t row = 1; row < rowCount - 1; ++row)
        {
            for (size_t column = 1; column < columnCount - 1; ++column)
            {
                int largestValue = std::max(grid[row - 1][column - 1], std::max(grid[row - 1][column], grid[row - 1][column + 1]));
                largestValue = std::max(largestValue, std::max(grid[row][column - 1], std::max(grid[row][column], grid[row][column + 1])));
                largestValue = std::max(largestValue, std::max(grid[row + 1][column - 1], std::max(grid[row + 1][column], grid[row + 1][column + 1])));
                result[row - 1][column - 1] = largestValue;
            }
        }
        return result;
    }
};

}

namespace LargestLocalValuesInMatrixTask
{

TEST(LargestLocalValuesInMatrixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{9, 9}, {8, 6}}),
              solution.largestLocal({{9, 9, 8, 1}, {5, 6, 2, 6}, {8, 2, 6, 4}, {6, 2, 2, 2}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{2, 2, 2}, {2, 2, 2}, {2, 2, 2}}),
              solution.largestLocal({{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 2, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}}));
}

}