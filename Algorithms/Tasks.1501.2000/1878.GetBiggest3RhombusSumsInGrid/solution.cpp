#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> getBiggestThree(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<int> biggest3Values;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                processCell(grid, biggest3Values, row, column);
            }
        }
        return biggest3Values;
    }

private:
    void processCell(std::vector<std::vector<int>> const &grid, std::vector<int> &biggest3Values, size_t row, size_t column) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t maxPossibleSize = std::min((columnCount - 1 - column) / 2, std::min(row, rowCount - row - 1));
        for (size_t size = 0; size <= maxPossibleSize; ++size)
            appendValue(biggest3Values, calcSum(grid, row, column, size));
    }

    [[nodiscard]] int calcSum(std::vector<std::vector<int>> const &grid, size_t row, size_t column, size_t size) const
    {
        if (size == 0)
            return grid[row][column];
        int sum = 0;
        const size_t leftColumn = column;
        const size_t rightColumn = leftColumn + 2 * size;
        for (size_t shift = 0; shift < size; ++shift)
            sum += grid[row - shift][column + shift];
        for (size_t shift = 0; shift < size; ++shift)
            sum += grid[row - size + shift][column + size + shift];
        for (size_t shift = 0; shift < size; ++shift)
            sum += grid[row + shift][column + 2 * size - shift];
        for (size_t shift = 0; shift < size; ++shift)
            sum += grid[row + size - shift][column + size - shift];
        return sum;
    }

    void appendValue(std::vector<int> &biggest3Values, int value) const
    {
        for (const int knownValue : biggest3Values)
        {
            if (knownValue == value)
                return;
        }
        biggest3Values.emplace_back(value);
        std::ranges::sort(biggest3Values, std::greater<int>());
        if (biggest3Values.size() > 3)
            biggest3Values.pop_back();
    }
};

}

namespace GetBiggest3RhombusSumsInGridTask
{

TEST(GetBiggest3RhombusSumsInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({228, 216, 211}),
              solution.getBiggestThree({{3, 4, 5, 1, 3}, {3, 3, 4, 2, 3}, {20, 30, 200, 40, 10}, {1, 5, 5, 4, 1}, {4, 3, 2, 2, 5}}));
    ASSERT_EQ(std::vector<int>({20, 9, 8}), solution.getBiggestThree({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    ASSERT_EQ(std::vector<int>({7}), solution.getBiggestThree({{7, 7, 7}}));
}

}