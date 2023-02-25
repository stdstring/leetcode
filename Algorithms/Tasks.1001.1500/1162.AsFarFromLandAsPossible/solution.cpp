#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDistance(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<size_t>> landDistances(rowCount, std::vector<size_t>(columnCount, INT_MAX));
        std::queue<CellData> queue;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] == 0)
                    continue;
                landDistances[row][column] = 0;
                if (((row > 0) && (grid[row - 1][column] == 0)) ||
                    ((row < rowMax) && (grid[row + 1][column] == 0)) ||
                    ((column > 0) && (grid[row][column - 1] == 0)) ||
                    ((column < columnMax) && (grid[row][column + 1] == 0)))
                    queue.emplace(row, column, 0);
            }
        }
        if (queue.empty() || (queue.size() == rowCount * columnCount))
            return -1;
        while (!queue.empty())
        {
            const CellData current(queue.front());
            const size_t row = current.Row;
            const size_t column = current.Column;
            const size_t nextDistance = current.Distance + 1;
            queue.pop();
            if ((row > 0) && (grid[row - 1][column] == 0) && (nextDistance < landDistances[row - 1][column]))
                processCell(row - 1, column, nextDistance, landDistances, queue);
            if ((row < rowMax) && (grid[row + 1][column] == 0) && (nextDistance < landDistances[row + 1][column]))
                processCell(row + 1, column, nextDistance, landDistances, queue);
            if ((column > 0) && (grid[row][column - 1] == 0) && (nextDistance < landDistances[row][column - 1]))
                processCell(row, column - 1, nextDistance, landDistances, queue);
            if ((column < columnMax) && (grid[row][column + 1] == 0) && (nextDistance < landDistances[row][column + 1]))
                processCell(row, column + 1, nextDistance, landDistances, queue);
        }
        size_t bestDistance = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                bestDistance = std::max(bestDistance, landDistances[row][column]);
            }
        }
        return static_cast<int>(bestDistance);
    }

private:
    struct CellData
    {
        CellData(size_t row, size_t column, size_t distance) : Row(row), Column(column), Distance(distance)
        {
        }

        size_t Row;
        size_t Column;
        size_t Distance;
    };

    void processCell(size_t row, size_t column, size_t distance, std::vector<std::vector<size_t>> &landDistances, std::queue<CellData> &queue) const
    {
        landDistances[row][column] = distance;
        queue.emplace(row, column, distance);
    }
};

}

namespace AsFarFromLandAsPossibleTask
{

TEST(AsFarFromLandAsPossibleTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxDistance({{1, 0, 1}, {0, 0, 0}, {1, 0, 1}}));
    ASSERT_EQ(4, solution.maxDistance({{1, 0, 0}, {0, 0, 0}, {0, 0, 0}}));
}

TEST(AsFarFromLandAsPossibleTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(-1, solution.maxDistance({{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}));
}

}
