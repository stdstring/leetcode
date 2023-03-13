#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> highestPeak(std::vector<std::vector<int>> const &isWater) const
    {
        constexpr int unknownValue = -1;
        const size_t rowCount = isWater.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = isWater.front().size();
        const size_t columnMax =  columnCount - 1;
        std::vector<std::vector<int>> heights(rowCount, std::vector<int>(columnCount, unknownValue));
        std::queue<std::pair<size_t, size_t>> queue;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (isWater[row][column] == 1)
                {
                    heights[row][column] = 0;
                    if (hasLandAdjacent(isWater, row, column))
                        queue.emplace(row, column);
                }
            }
        }
        while (!queue.empty())
        {
            auto [row, column] = queue.front();
            queue.pop();
            const int height = heights[row][column];
            if ((row > 0) && (heights[row - 1][column] == unknownValue))
            {
                heights[row - 1][column] = height + 1;
                queue.emplace(row - 1, column);
            }
            if ((row < rowMax) && (heights[row + 1][column] == unknownValue))
            {
                heights[row + 1][column] = height + 1;
                queue.emplace(row + 1, column);
            }
            if ((column > 0) && (heights[row][column - 1] == unknownValue))
            {
                heights[row][column - 1] = height + 1;
                queue.emplace(row, column - 1);
            }
            if ((column < columnMax) && (heights[row][column + 1] == unknownValue))
            {
                heights[row][column + 1] = height + 1;
                queue.emplace(row, column + 1);
            }
        }
        return heights;
    }

private:
    [[nodiscard]] bool hasLandAdjacent(std::vector<std::vector<int>> const &isWater, size_t row, size_t column) const
    {
        const size_t rowMax = isWater.size() - 1;
        const size_t columnMax = isWater.front().size() - 1;
        return ((row > 0) && (isWater[row - 1][column] == 0)) ||
               ((row < rowMax) && (isWater[row + 1][column] == 0)) ||
               ((column > 0) && (isWater[row][column - 1] == 0)) ||
               ((column < columnMax) && (isWater[row][column + 1] == 0));
    }
};

}

namespace MapHighestPeakTask
{

TEST(MapHighestPeakTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 0}, {2, 1}}), solution.highestPeak({{0, 1}, {0, 0}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1, 0}, {0, 1, 1}, {1, 2, 2}}), solution.highestPeak({{0, 0, 1}, {1, 0, 0}, {0, 0, 0}}));
}

}