#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxPoints(std::vector<std::vector<int>> const &points) const
    {
        const size_t rowCount = points.size();
        const size_t columnCount = points.front().size();
        std::vector<long long> currentDp(columnCount, 0);
        for (size_t column = 0; column < columnCount; ++column)
            currentDp[column] = points[0][column];
        std::vector<long long> nextDp(columnCount, 0);
        for (size_t row = 1; row < rowCount; ++row)
        {
            std::vector<long long> leftMax(columnCount, 0);
            leftMax[0] = currentDp[0] + 0;
            std::vector<long long> rightMax(columnCount, 0);
            rightMax[columnCount - 1] = currentDp[columnCount - 1] - static_cast<long long>(columnCount - 1);
            for (size_t shift = 1; shift < columnCount; ++ shift)
            {
                size_t leftIndex = 0 + shift;
                size_t rightIndex = columnCount - 1 - shift;
                leftMax[leftIndex] = std::max(leftMax[leftIndex - 1], currentDp[leftIndex] + static_cast<long long>(leftIndex));
                rightMax[rightIndex] = std::max(rightMax[rightIndex + 1], currentDp[rightIndex] - static_cast<long long>(rightIndex));
            }
            for (size_t column = 0; column < columnCount; ++column)
            {
                const long long currentColumn = static_cast<long long>(column);
                nextDp[column] = std::max(leftMax[column] - currentColumn, rightMax[column] + currentColumn) + points[row][column];
            }
            std::swap(currentDp, nextDp);
        }
        return *std::ranges::max_element(currentDp);
    }
};

}

namespace MaxNumberPointsWithCostTask
{

TEST(MaxNumberPointsWithCostTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.maxPoints({{1, 2, 3}, {1, 5, 1}, {3, 1, 1}}));
    ASSERT_EQ(11, solution.maxPoints({{1, 5}, {2, 3}, {4, 2}}));
}

}