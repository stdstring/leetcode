#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxMatrixSum(std::vector<std::vector<int>> const &matrix) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        int negativeCount = 0;
        int minAbsValue = INT_MAX;
        long long absSum = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (matrix[row][column] < 0)
                    ++negativeCount;
                minAbsValue = std::min(minAbsValue, std::abs(matrix[row][column]));
                absSum += 1LL * std::abs(matrix[row][column]);
            }
        }
        if ((negativeCount % 2) != 0)
            absSum -= 2LL * minAbsValue;
        return absSum;
    }
};

}

namespace MaxMatrixSumTask
{

TEST(MaxMatrixSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxMatrixSum({{1, -1}, {-1, 1}}));
    ASSERT_EQ(16, solution.maxMatrixSum({{1, 2, 3}, {-1, -2, -3}, {1, 2, 3}}));
}

TEST(MaxMatrixSumTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxMatrixSum({{1, 0}, {-1, 1}}));
}

}