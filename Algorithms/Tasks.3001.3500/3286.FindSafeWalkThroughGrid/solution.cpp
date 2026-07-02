#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool findSafeWalk(std::vector<std::vector<int>> const &grid, int health) const
    {
        if ((health == 1) && (grid[0][0] == 1))
            return false;
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<int>> healthGrid(rowCount, std::vector<int>(columnCount, 0));
        healthGrid[0][0] = health - grid[0][0];
        std::queue<Step> steps;
        steps.emplace(0, 0, healthGrid[0][0]);
        while (!steps.empty())
        {
            const Step current(steps.front());
            steps.pop();
            if ((current.row == rowMax) && (current.column == columnMax))
                return true;
            if (current.row > 0)
                processNextStep(grid, current.row - 1, current.column, current.health, healthGrid, steps);
            if (current.row < rowMax)
                processNextStep(grid, current.row + 1, current.column, current.health, healthGrid, steps);
            if (current.column > 0)
                processNextStep(grid, current.row, current.column - 1, current.health, healthGrid, steps);
            if (current.column < columnMax)
                processNextStep(grid, current.row, current.column + 1, current.health, healthGrid, steps);
        }
        return false;
    }

private:
    struct Step
    {
        size_t row;
        size_t column;
        int health;
    };

    void processNextStep(std::vector<std::vector<int>> const &grid,
                         size_t row,
                         size_t column,
                         int prevHealth,
                         std::vector<std::vector<int>> &healthGrid,
                         std::queue<Step> &steps) const
    {
        int health = prevHealth - grid[row][column];
        if (health == 0)
            return;
        if (health <= healthGrid[row][column])
            return;
        healthGrid[row][column] = health;
        steps.emplace(row, column, health);
    }
};

}

namespace FindSafeWalkThroughGridTask
{

TEST(FindSafeWalkThroughGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.findSafeWalk({{0, 1, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 1, 0}}, 1));
    ASSERT_EQ(false, solution.findSafeWalk({{0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0}, {0, 1, 1, 1, 0, 1}, {0, 0, 1, 0, 1, 0}}, 3));
    ASSERT_EQ(true, solution.findSafeWalk({{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, 5));
}

}
