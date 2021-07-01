#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minFallingPathSum(std::vector<std::vector<int>> const &matrix) const
    {
        std::vector<int> currentRowSums(matrix.front().size(), 0);
        for (std::vector<int> const &row : matrix)
        {
            std::vector<int> nextRowSums(matrix.front().size(), INT_MAX);
            for (size_t index = 0; index < row.size(); ++index)
            {
                nextRowSums[index] = std::min(nextRowSums[index], currentRowSums[index] + row[index]);
                if (index > 0)
                    nextRowSums[index - 1] = std::min(nextRowSums[index - 1], currentRowSums[index] + row[index - 1]);
                if (index < row.size() - 1)
                    nextRowSums[index + 1] = std::min(nextRowSums[index + 1], currentRowSums[index] + row[index + 1]);
            }
            std::swap(currentRowSums, nextRowSums);
        }
        return *std::min_element(currentRowSums.cbegin(), currentRowSums.cend());
    }
};

}

namespace MinimumFallingPathSumTask
{

TEST(MinimumFallingPathSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(13, solution.minFallingPathSum({{2, 1, 3}, {6, 5, 4}, {7, 8, 9}}));
    ASSERT_EQ(-59, solution.minFallingPathSum({{-19, 57}, {-40, -5}}));
    ASSERT_EQ(-48, solution.minFallingPathSum({{-48}}));
}

}