#include <map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minCost(std::vector<std::vector<int>> const &grid) const
    {
        const size_t right = 1;
        const size_t left = 2;
        const size_t bottom = 3;
        const size_t top = 4;
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<int>> costs(rowCount, std::vector<int>(columnCount, INT_MAX));
        costs[0][0] = 0;
        std::vector<std::vector<bool>> visited(rowCount, std::vector<bool>(columnCount, false));
        typedef std::pair<size_t, size_t> TCell;
        std::multimap<int, TCell> cellQueue;
        cellQueue.emplace(0, TCell(0, 0));
        while (!cellQueue.empty())
        {
            const int currentCost = cellQueue.cbegin()->first;
            const size_t row = cellQueue.cbegin()->second.first;
            const size_t column = cellQueue.cbegin()->second.second;
            cellQueue.erase(cellQueue.cbegin());
            if (visited[row][column])
                continue;
            visited[row][column] = true;
            int currentSign = grid[row][column];
            if ((column > 0) && processNextCell(row, column - 1, currentCost + (currentSign == left ? 0 : 1), visited, costs))
                cellQueue.emplace(currentCost + (currentSign == left ? 0 : 1), TCell(row, column - 1));
            if ((column < (columnCount - 1)) && processNextCell(row, column + 1, currentCost + (currentSign == right ? 0 : 1), visited, costs))
                cellQueue.emplace(currentCost + (currentSign == right ? 0 : 1), TCell(row, column + 1));
            if ((row > 0) && processNextCell(row - 1, column, currentCost + (currentSign == top ? 0 : 1), visited, costs))
                cellQueue.emplace(currentCost + (currentSign == top ? 0 : 1), TCell(row - 1, column));
            if ((row < (rowCount - 1)) && processNextCell(row + 1, column, currentCost + (currentSign == bottom ? 0 : 1), visited, costs))
                cellQueue.emplace(currentCost + (currentSign == bottom ? 0 : 1), TCell(row + 1, column));
        }
        return costs.back().back();
    }

private:
    [[nodiscard]] bool processNextCell(size_t row, size_t column, int cost, std::vector<std::vector<bool>> const &visited, std::vector<std::vector<int>> &costs) const
    {
        if (visited[row][column])
            return false;
        if (cost >= costs[row][column])
            return false;
        costs[row][column] = cost;
        return true;
    }
};

}

namespace MinCostMakeAtLeastOneValidPathInGridTask
{

TEST(MinCostMakeAtLeastOneValidPathInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minCost({{1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}, {2, 2, 2, 2}}));
    ASSERT_EQ(0, solution.minCost({{1, 1, 3}, {3, 2, 2}, {1, 1, 4}}));
    ASSERT_EQ(1, solution.minCost({{1, 2}, {4, 3}}));
}

TEST(MinCostMakeAtLeastOneValidPathInGridTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minCost({{1, 3, 3, 3}, {2, 2, 1, 2}, {4, 3, 3, 4}, {3, 2, 2, 3}, {3, 2, 1, 3}, {4, 1, 4, 3}, {3, 3, 1, 2}}));
    ASSERT_EQ(0, solution.minCost({{1, 1, 1, 3}, {3, 2, 2, 2}, {1, 1, 1, 3}, {3, 2, 2, 2}}));
}

}