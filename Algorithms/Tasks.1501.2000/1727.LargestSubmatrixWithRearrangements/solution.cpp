#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestSubmatrix(std::vector<std::vector<int>> const &matrix) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::vector<size_t> currentHeights(columnCount, 0);
        size_t bestArea = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                currentHeights[column] = matrix[row][column] == 0 ? 0 : currentHeights[column] + 1;
            std::vector<size_t> currentRow(currentHeights);
            std::ranges::sort(currentRow, std::greater<int>());
            for (size_t column = 0; column < columnCount; ++column)
                bestArea = std::max(bestArea, currentRow[column] * (1 + column));
        }
        return static_cast<int>(bestArea);
    }
};

}

namespace LargestSubmatrixWithRearrangementsTask
{

TEST(LargestSubmatrixWithRearrangementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.largestSubmatrix({{0, 0, 1}, {1, 1, 1}, {1, 0, 1}}));
    ASSERT_EQ(3, solution.largestSubmatrix({{1, 0, 1, 0, 1}}));
    ASSERT_EQ(2, solution.largestSubmatrix({{1, 1, 0}, {1, 0, 1}}));
}

TEST(LargestSubmatrixWithRearrangementsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.largestSubmatrix({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}));
}

}