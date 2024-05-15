#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumSafenessFactor(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        if ((grid[0][0] == 1) || (grid[rowMax][columnMax] == 1))
            return 0;
        const std::vector<std::vector<int>> safenessMatrix(generateSafenessMatrix(grid));
        std::queue<TPoint> movesQueue;
        std::vector<std::vector<int>> distancesMatrix(rowCount, std::vector<int>(columnCount, 0));
        distancesMatrix[0][0] = safenessMatrix[0][0];
        movesQueue.emplace(0, 0);
        while (!movesQueue.empty())
        {
            auto [row, column] = movesQueue.front();
            movesQueue.pop();
            int distance = distancesMatrix[row][column];
            if ((row > 0) && (grid[row - 1][column] == 0) && (distancesMatrix[row - 1][column] < std::min(distance, safenessMatrix[row - 1][column])))
            {
                movesQueue.emplace(row - 1, column);
                distancesMatrix[row - 1][column] = std::max(distancesMatrix[row - 1][column], std::min(distance, safenessMatrix[row - 1][column]));
            }
            if ((row < rowMax) && (grid[row + 1][column] == 0) && (distancesMatrix[row + 1][column] < std::min(distance, safenessMatrix[row + 1][column])))
            {
                movesQueue.emplace(row + 1, column);
                distancesMatrix[row + 1][column] = std::max(distancesMatrix[row + 1][column], std::min(distance, safenessMatrix[row + 1][column]));
            }
            if ((column > 0) && (grid[row][column - 1] == 0) && (distancesMatrix[row][column - 1] < std::min(distance, safenessMatrix[row][column - 1])))
            {
                movesQueue.emplace(row, column - 1);
                distancesMatrix[row][column - 1] = std::max(distancesMatrix[row][column - 1], std::min(distance, safenessMatrix[row][column - 1]));
            }
            if ((column < columnMax) && (grid[row][column + 1] == 0) && (distancesMatrix[row][column + 1] < std::min(distance, safenessMatrix[row][column + 1])))
            {
                movesQueue.emplace(row, column + 1);
                distancesMatrix[row][column + 1] = std::max(distancesMatrix[row][column + 1], std::min(distance, safenessMatrix[row][column + 1]));
            }
        }
        return distancesMatrix[rowMax][columnMax];
    }

private:
    typedef std::pair<size_t, size_t> TPoint;

    [[nodiscard]] std::vector<std::vector<int>> generateSafenessMatrix(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<int>> safenessMatrix(rowCount, std::vector<int>(columnCount, INT_MAX));
        std::queue<TPoint> safenessQueue;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] == 1)
                {
                    safenessQueue.emplace(row, column);
                    safenessMatrix[row][column] = 0;
                }
            }
        }
        while (!safenessQueue.empty())
        {
            auto [row, column] = safenessQueue.front();
            const int nextDistance = safenessMatrix[row][column] + 1;
            safenessQueue.pop();
            if ((row > 0) && (nextDistance < safenessMatrix[row - 1][column]))
            {
                if (safenessMatrix[row - 1][column] == INT_MAX)
                    safenessQueue.emplace(row - 1, column);
                safenessMatrix[row - 1][column] = nextDistance;
            }
            if ((row < rowMax) && (nextDistance < safenessMatrix[row + 1][column]))
            {
                if (safenessMatrix[row + 1][column] == INT_MAX)
                    safenessQueue.emplace(row + 1, column);
                safenessMatrix[row + 1][column] = nextDistance;
            }
            if ((column > 0) && (nextDistance < safenessMatrix[row][column - 1]))
            {
                if (safenessMatrix[row][column - 1] == INT_MAX)
                    safenessQueue.emplace(row, column - 1);
                safenessMatrix[row][column - 1] = nextDistance;
            }
            if ((column < columnMax) && (nextDistance < safenessMatrix[row][column + 1]))
            {
                if (safenessMatrix[row][column + 1] == INT_MAX)
                    safenessQueue.emplace(row, column + 1);
                safenessMatrix[row][column + 1] = nextDistance;
            }
        }
        return safenessMatrix;
    }
};

}

namespace FindSafestPathInGridTask
{

TEST(FindSafestPathInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.maximumSafenessFactor({{1, 0, 0}, {0, 0, 0}, {0, 0, 1}}));
    ASSERT_EQ(2, solution.maximumSafenessFactor({{0, 0, 1}, {0, 0, 0}, {0, 0, 0}}));
    ASSERT_EQ(2, solution.maximumSafenessFactor({{0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}}));
}

TEST(FindSafestPathInGridTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maximumSafenessFactor({{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                                                 {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
                                                 {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
                                                 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                                                 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                                 {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                                 {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}}));
}

}