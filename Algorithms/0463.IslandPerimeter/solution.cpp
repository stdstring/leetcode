#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int islandPerimeter(std::vector<std::vector<int>> const &grid) const
    {
        const std::vector<int> zeroRow(grid.front().size(), 0);
        int perimeter = perimeterForLine(grid.front(), zeroRow);
        for (size_t index = 1; index < grid.size(); ++index)
            perimeter += perimeterForLine(grid[index], grid[index - 1]);
        perimeter += perimeterForLine(zeroRow, grid.back());
        return perimeter;
    }

private:
    int perimeterForLine(std::vector<int> const &current, std::vector<int> const &prev) const
    {
        int perimeter = 0;
        for (size_t index = 0; index < current.size(); ++index)
        {
            if (current[index] != prev[index])
                ++perimeter;
            if (current[index] == 1 && (index == 0 || current[index - 1] == 0))
                ++perimeter;
            if (current[index] == 1 && (index == (current.size() - 1) || current[index + 1] == 0))
                ++perimeter;
        }
        return perimeter;
    }
};

}

namespace IslandPerimeterTask
{

TEST(IslandPerimeterTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(16, solution.islandPerimeter({{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}}));
    ASSERT_EQ(4, solution.islandPerimeter({{1}}));
    ASSERT_EQ(4, solution.islandPerimeter({{1, 0}}));
}

}