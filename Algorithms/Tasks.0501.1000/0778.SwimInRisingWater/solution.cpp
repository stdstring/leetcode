#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int swimInWater(std::vector<std::vector<int>> const &grid) const
    {
        const size_t n = grid.size();
        const size_t coordMax = n - 1;
        std::vector<std::vector<int>> gridTimes(n, std::vector<int>(n, INT_MAX));
        std::vector<std::vector<bool>> processed(n, std::vector<bool>(n, false));
        auto cmp = [](CellData const& l, CellData const& r) { return l.Time > r.Time; };
        std::priority_queue<CellData, std::vector<CellData>, decltype(cmp)> queue(cmp);
        gridTimes[0][0] = grid[0][0];
        queue.emplace(0, 0, grid[0][0]);
        while (!queue.empty())
        {
            const CellData current(queue.top());
            const size_t row = current.Row;
            const size_t column = current.Column;
            const int time = current.Time;
            queue.pop();
            if (processed[row][column])
                continue;
            processed[row][column] = true;
            if ((row > 0) && (std::max(time, grid[row - 1][column]) < gridTimes[row - 1][column]))
            {
                gridTimes[row - 1][column] = std::max(time, grid[row - 1][column]);
                queue.emplace(row - 1, column, gridTimes[row - 1][column]);
            }
            if ((row < coordMax) && (std::max(time, grid[row + 1][column]) < gridTimes[row + 1][column]))
            {
                gridTimes[row + 1][column] = std::max(time, grid[row + 1][column]);
                queue.emplace(row + 1, column, gridTimes[row + 1][column]);
            }
            if ((column > 0) && (std::max(time, grid[row][column - 1]) < gridTimes[row][column - 1]))
            {
                gridTimes[row][column - 1] = std::max(time, grid[row][column - 1]);
                queue.emplace(row, column - 1, gridTimes[row][column - 1]);
            }
            if ((column < coordMax) && (std::max(time, grid[row][column + 1]) < gridTimes[row][column + 1]))
            {
                gridTimes[row][column + 1] = std::max(time, grid[row][column + 1]);
                queue.emplace(row, column + 1, gridTimes[row][column + 1]);
            }
        }
        return gridTimes.back().back();
    }

private:
    struct CellData
    {
        CellData(size_t row, size_t column, int time) : Row(row), Column(column), Time(time)
        {
        }
        size_t Row;
        size_t Column;
        int Time;
    };
};

}

namespace SwimInRisingWaterTask
{

TEST(SwimInRisingWaterTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.swimInWater({{0, 2}, {1, 3}}));
    ASSERT_EQ(16, solution.swimInWater({{0, 1, 2, 3, 4}, {24, 23, 22, 21, 5}, {12, 13, 14, 15, 16}, {11, 17, 18, 19, 20}, {10, 9, 8, 7, 6}}));
}

TEST(SwimInRisingWaterTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.swimInWater({{2, 3}, {0, 1}}));
}

}