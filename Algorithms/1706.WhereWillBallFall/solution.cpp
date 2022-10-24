#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findBall(std::vector<std::vector<int>> const &grid) const
    {
        const size_t columnCount = grid.front().size();
        std::vector<int> result(columnCount, -1);
        for (size_t column = 0; column < columnCount; ++column)
            result[column] = processBall(grid, column);
        return result;
    }

private:
    [[nodiscard]] bool canMove(std::vector<std::vector<int>> const &grid, size_t row, size_t column) const
    {
        const size_t columnMax = grid.front().size() - 1;
        if ((column == 0) && (grid[row][column] == -1))
            return false;
        if ((column == columnMax) && (grid[row][column] == 1))
            return false;
        if ((grid[row][column] == 1) && (grid[row][column + 1] == -1))
            return false;
        if ((grid[row][column] == -1) && (grid[row][column - 1] == 1))
            return false;
        return true;
    }

    [[nodiscard]] int processBall(std::vector<std::vector<int>> const &grid, size_t column) const
    {
        for (size_t row = 0; row < grid.size(); ++row)
        {
            if (!canMove(grid, row, column))
                return -1;
            if (grid[row][column] == 1)
                ++column;
            else
                --column;
        }
        return static_cast<int>(column);
    }
};

}

namespace WhereWillBallFallTask
{

TEST(WhereWillBallFallTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, -1, -1, -1, -1}),
              solution.findBall({{1, 1, 1, -1, -1}, {1, 1, 1, -1, -1}, {-1, -1, -1, 1, 1}, {1, 1, 1, 1, -1}, {-1, -1, -1, -1, -1}}));
    ASSERT_EQ(std::vector<int>({-1}), solution.findBall({{-1}}));
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3, 4, -1}),
              solution.findBall({{1, 1, 1, 1, 1, 1}, {-1, -1, -1, -1, -1, -1}, {1, 1, 1, 1, 1, 1}, {-1, -1, -1, -1, -1, -1}}));
}

}