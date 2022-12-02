#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> onesMinusZeros(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<int> rowOnes(rowCount, 0);
        std::vector<int> rowZeros(rowCount, 0);
        std::vector<int> columnOnes(columnCount, 0);
        std::vector<int> columnZeros(columnCount, 0);
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] == 1)
                {
                    ++rowOnes[row];
                    ++columnOnes[column];
                }
                else
                {
                    ++rowZeros[row];
                    ++columnZeros[column];
                }
            }
        }
        std::vector<std::vector<int>> result(rowCount, std::vector<int>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                result[row][column] = rowOnes[row] - rowZeros[row] + columnOnes[column] - columnZeros[column];
        }
        return result;
    }
};

}

namespace DiffBetweenOnesZerosInRowColumnTask
{

TEST(DiffBetweenOnesZerosInRowColumnTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0, 4}, {0, 0, 4}, {-2, -2, 2}}),
              solution.onesMinusZeros({{0, 1, 1}, {1, 0, 1}, {0, 0, 1}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{5, 5, 5}, {5, 5, 5}}),
              solution.onesMinusZeros({{1, 1, 1}, {1, 1, 1}}));
}

}