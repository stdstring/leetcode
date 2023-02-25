#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Step
{
    Step(size_t row, size_t column, int k) : Row(row), Column(column), K(k)
    {
    }

    size_t Row;
    size_t Column;
    int K;
};

class Solution
{
public:
    [[nodiscard]] int shortestPath(std::vector<std::vector<int>> const &grid, int k) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        if ((rowMax == 0) && (columnMax == 0))
            return 0;
        std::vector<std::vector<std::vector<int>>> steps(rowCount, std::vector<std::vector<int>>(columnCount, std::vector<int>(k + 1, INT_MAX)));
        steps[0][0][k] = 0;
        std::queue<Step> stepQueue;
        stepQueue.emplace(0, 0, k);
        while (!stepQueue.empty())
        {
            const size_t row = stepQueue.front().Row;
            const size_t column = stepQueue.front().Column;
            const int currentK = stepQueue.front().K;
            stepQueue.pop();
            const int currentStep = steps[row][column][currentK];
            if (((row == rowMax) && (column + 1 == columnMax)) || ((row + 1 == rowMax) && (column == columnMax)))
                return currentStep + 1;
            // left
            if ((column > 0) && ((grid[row][column - 1] == 0) || (currentK > 0)))
                processNextStep(stepQueue, steps, row, column - 1, currentK, currentStep, grid[row][column - 1]);
            // right
            if ((column < columnMax) && ((grid[row][column + 1] == 0) || (currentK > 0)))
                processNextStep(stepQueue, steps, row, column + 1, currentK, currentStep, grid[row][column + 1]);
            // top
            if ((row > 0) && ((grid[row - 1][column] == 0) || (currentK > 0)))
                processNextStep(stepQueue, steps, row - 1, column, currentK, currentStep, grid[row - 1][column]);
            // bottom
            if ((row < rowMax) && ((grid[row + 1][column] == 0) || (currentK > 0)))
                processNextStep(stepQueue, steps, row + 1, column, currentK, currentStep, grid[row + 1][column]);
        }
        return -1;
    }

private:
    void processNextStep(std::queue<Step> &stepQueue,
                         std::vector<std::vector<std::vector<int>>> &steps,
                         size_t nextRow,
                         size_t nextColumn,
                         int currentK,
                         int currentStep,
                         int nextCell) const
    {
        const int nextK = currentK - nextCell;
        const int step = steps[nextRow][nextColumn][nextK];
        if (currentStep + 1 < step)
        {
            steps[nextRow][nextColumn][nextK] = currentStep + 1;
            stepQueue.emplace(nextRow, nextColumn, nextK);
        }
    }
};

}

namespace ShortestPathInGridWithObstaclesEliminationTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.shortestPath({{0, 0, 0}, {1, 1, 0}, {0, 0, 0}, {0, 1, 1}, {0, 0, 0}}, 1));
    ASSERT_EQ(-1, solution.shortestPath({{0, 1, 1}, {1, 1, 1}, {1, 0, 0}}, 1));
}

TEST(TwoSumTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.shortestPath({{0}}, 1));
}

}