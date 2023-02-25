#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> shiftGrid(std::vector<std::vector<int>> const &grid, int k) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<int> data;
        data.reserve(rowCount * columnCount);
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                data.push_back(grid[row][column]);
            }
        }
        std::vector<std::vector<int>> result(rowCount, std::vector<int>(columnCount, 0));
        for (size_t index = 0; index < data.size(); ++index)
        {
            const size_t shiftedIndex = (index + k) % data.size();
            result[shiftedIndex / columnCount][shiftedIndex % columnCount] = data[index];
        }
        return result;
    }
};

}

namespace Shift2DGridTask
{

TEST(Shift2DGridTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{9, 1, 2}, {3, 4, 5}, {6, 7, 8}}), solution.shiftGrid({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 1));
    ASSERT_EQ(std::vector<std::vector<int>>({{12, 0, 21, 13}, {3, 8, 1, 9}, {19, 7, 2, 5}, {4, 6, 11, 10}}), solution.shiftGrid({{3, 8, 1, 9}, {19, 7, 2, 5}, {4, 6, 11, 10}, {12, 0, 21, 13}}, 4));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}), solution.shiftGrid({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 9));
}

}