#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSideLength(std::vector<std::vector<int>> const &mat, int threshold) const
    {
        const size_t rowCount = mat.size();
        const size_t columnCount = mat.back().size();
        const std::vector<std::vector<int>> prefixSum(createPrefixSum(mat));
        size_t bestLength = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (threshold < mat[row][column])
                    continue;
                bestLength = std::max(bestLength, findBestSizeLength(prefixSum, row, column, threshold));
            }
        }
        return static_cast<int>(bestLength);
    }

private:
    [[nodiscard]] std::vector<std::vector<int>> createPrefixSum(std::vector<std::vector<int>> const &mat) const
    {
        const size_t rowCount = mat.size();
        const size_t columnCount = mat.back().size();
        std::vector<std::vector<int>> prefixSum(rowCount, std::vector<int>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                prefixSum[row][column] = mat[row][column] +
                                         (row > 0 ? prefixSum[row - 1][column] : 0) +
                                         (column > 0 ? prefixSum[row][column - 1] : 0) -
                                         ((row > 0) && (column > 0) ? prefixSum[row - 1][column - 1] : 0);
        }
        return prefixSum;
    }

    [[nodiscard]] size_t findBestSizeLength(std::vector<std::vector<int>> const &prefixSum, size_t row, size_t column, int threshold) const
    {
        const size_t rowCount = prefixSum.size();
        const size_t columnCount = prefixSum.back().size();
        const size_t maxSideLength = std::min(rowCount - row, columnCount - column);
        const int maxPrefixSumValue = prefixSum[row + maxSideLength - 1][column + maxSideLength - 1] -
                                      (row > 0 ? prefixSum[row - 1][column + maxSideLength - 1] : 0) -
                                      (column > 0 ? prefixSum[row + maxSideLength - 1][column - 1] : 0) +
                                      ((row > 0) && (column > 0) ? prefixSum[row - 1][column - 1] : 0);
        if (maxPrefixSumValue <= threshold)
            return maxSideLength;
        size_t left = 1;
        size_t right = maxSideLength;
        while ((right - left) > 1)
        {
            const size_t middle = (left + right) / 2;
            const int middleValue = prefixSum[row + middle - 1][column + middle - 1] -
                                    (row > 0 ? prefixSum[row - 1][column + middle - 1] : 0) -
                                    (column > 0 ? prefixSum[row + middle - 1][column - 1] : 0) +
                                    ((row > 0) && (column > 0) ? prefixSum[row - 1][column - 1] : 0);
            if (threshold == middleValue)
                return middle;
            if (threshold < middleValue)
                right = middle - 1;
            else
                left = middle;
        }
        return left;
    }
};

}

namespace MaxSideLengthOfSquareSumLTEThresholdTask
{

TEST(MaxSideLengthOfSquareSumLTEThresholdTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxSideLength({{1, 1, 3, 2, 4, 3, 2}, {1, 1, 3, 2, 4, 3, 2}, {1, 1, 3, 2, 4, 3, 2}}, 4));
    ASSERT_EQ(0, solution.maxSideLength({{2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}}, 1));
}

}