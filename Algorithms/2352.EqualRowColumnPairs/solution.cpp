#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int equalPairs(std::vector<std::vector<int>> const &grid) const
    {
        const size_t gridSize = grid.size();
        std::unordered_map<int, std::vector<size_t>> rowHashCodeMap;
        for (size_t row = 0; row < gridSize; ++row)
        {
            int rowHashCode = calcRowHashCode(grid[row]);
            auto iterator = rowHashCodeMap.find(rowHashCode);
            if (iterator == rowHashCodeMap.end())
                iterator = rowHashCodeMap.emplace(rowHashCode, std::vector<size_t>()).first;
            iterator->second.push_back(row);
        }
        size_t pairsCount = 0;
        for (size_t column = 0; column < gridSize; ++column)
        {
            int columnHashCode = calcColumnHashCode(grid, column);
            auto iterator = rowHashCodeMap.find(columnHashCode);
            if (iterator != rowHashCodeMap.cend())
            {
                for (const size_t row : iterator->second)
                {
                    if (compareRowColumn(grid, row, column))
                        ++pairsCount;
                }
            }
        }
        return static_cast<int>(pairsCount);
    }

private:
    [[nodiscard]] int calcRowHashCode(std::vector<int> const &row) const
    {
        size_t result = 0;
        for (int value : row)
            result ^= (std::hash<int>{}(value) << 1);
        return static_cast<int>(result);
    }

    [[nodiscard]] int calcColumnHashCode(std::vector<std::vector<int>> const &grid, size_t column) const
    {
        size_t result = 0;
        for (std::vector<int> const &row : grid)
            result ^= (std::hash<int>{}(row[column]) << 1);
        return static_cast<int>(result);
    }

    [[nodiscard]] bool compareRowColumn(std::vector<std::vector<int>> const &grid, size_t row, size_t column) const
    {
        for (size_t index = 0; index < grid.size(); ++index)
        {
            if (grid[row][index] != grid[index][column])
                return false;
        }
        return true;
    }
};

}

namespace EqualRowColumnPairsTask
{

TEST(EqualRowColumnPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.equalPairs({{3, 2, 1}, {1, 7, 6}, {2, 7, 7}}));
    ASSERT_EQ(3, solution.equalPairs({{3, 1, 2, 2}, {1, 4, 4, 5}, {2, 4, 2, 2}, {2, 4, 2, 2}}));
}

}
