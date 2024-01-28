#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSubmatrixSumTarget(std::vector<std::vector<int>> const &matrix, int target) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::vector<std::vector<int>> rowPrefixSums(rowCount, std::vector<int>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                rowPrefixSums[row][column] = matrix[row][column] + (column > 0 ? rowPrefixSums[row][column - 1] : 0);
        }
        size_t submatrixCount = 0;
        for (size_t fromColumn = 0; fromColumn < columnCount; ++fromColumn)
        {
            for (size_t toColumn = fromColumn; toColumn < columnCount; ++toColumn)
            {
                std::unordered_map<int, size_t> submatrixSumMap;
                submatrixSumMap[0] = 1;
                int totalSum = 0;
                for (size_t row = 0; row < rowCount; ++row)
                {
                    totalSum += rowPrefixSums[row][toColumn];
                    if (fromColumn > 0)
                        totalSum -= rowPrefixSums[row][fromColumn - 1];
                    if (submatrixSumMap.contains(totalSum - target))
                        submatrixCount += submatrixSumMap[totalSum - target];
                    ++submatrixSumMap[totalSum];
                }
            }
        }
        return static_cast<int>(submatrixCount);
    }
};

}

namespace NumberSubmatricesThatSumToTargetTask
{

TEST(NumberSubmatricesThatSumToTargetTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.numSubmatrixSumTarget({{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}, 0));
    ASSERT_EQ(5, solution.numSubmatrixSumTarget({{1, -1}, {-1, 1}}, 0));
    ASSERT_EQ(0, solution.numSubmatrixSumTarget({{904}}, 0));
}

}