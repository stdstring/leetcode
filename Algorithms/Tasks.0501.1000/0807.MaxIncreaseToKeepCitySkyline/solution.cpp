#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxIncreaseKeepingSkyline(std::vector<std::vector<int>> const &grid) const
    {
        std::vector<int> horizontalMaxHeights(grid.front().size(), 0);
        std::vector<int> verticalMaxHeights(grid.size(), 0);
        for (size_t row = 0; row < grid.size(); ++row)
        {
            for (size_t column = 0; column < grid.size(); ++column)
            {
                horizontalMaxHeights[column] = std::max(horizontalMaxHeights[column], grid[row][column]);
                verticalMaxHeights[row] = std::max(verticalMaxHeights[row], grid[row][column]);
            }
        }
        int maxTotalSum = 0;
        for (size_t row = 0; row < grid.size(); ++row)
        {
            for (size_t column = 0; column < grid.size(); ++column)
            {
                maxTotalSum += (std::min(verticalMaxHeights[row], horizontalMaxHeights[column]) - grid[row][column]);
            }
        }
        return maxTotalSum;
    }
};

}

namespace MaxIncreaseToKeepCitySkylineTask
{

TEST(MaxIncreaseToKeepCitySkylineTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(35, solution.maxIncreaseKeepingSkyline({{3, 0, 8, 4}, {2, 4, 5, 7}, {9, 2, 6, 3}, {0, 3, 1, 0}}));
    ASSERT_EQ(0, solution.maxIncreaseKeepingSkyline({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}));
}

}