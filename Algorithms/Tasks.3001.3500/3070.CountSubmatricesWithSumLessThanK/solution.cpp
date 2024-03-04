#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countSubmatrices(std::vector<std::vector<int>> const &grid, int k) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<int>> prefixSum(rowCount, std::vector<int>(columnCount, 0));
        size_t submatricesCount = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            if ((row > 0) && (prefixSum[row - 1][0] > k))
                break;
            int rowPrefixSum = 0;
            for (size_t column = 0; column < columnCount; ++column)
            {
                rowPrefixSum += grid[row][column];
                prefixSum[row][column] = (row > 0 ? prefixSum[row - 1][column] : 0) + rowPrefixSum;
                if (prefixSum[row][column] > k)
                    break;
                ++submatricesCount;
            }
        }
        return static_cast<int>(submatricesCount);
    }
};

}

namespace CountSubmatricesWithSumLessThanKTask
{

TEST(CountSubmatricesWithSumLessThanKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.countSubmatrices({{7, 6, 3}, {6, 6, 1}}, 18));
    ASSERT_EQ(6, solution.countSubmatrices({{7, 2, 9}, {1, 5, 0}, {2, 6, 6}}, 20));
}

}