#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int kthLargestValue(std::vector<std::vector<int>> const &matrix, int k) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::vector<int> xorValues;
        xorValues.reserve(rowCount * columnCount);
        std::vector<int> xorRow(columnCount, 0);
        for (size_t row = 0; row < rowCount; ++row)
        {
            int prevXorRow = 0;
            for (size_t column = 0; column < columnCount; ++column)
            {
                const int currentXorValue = xorRow[column] ^ prevXorRow ^ matrix[row][column];
                xorRow[column] = currentXorValue;
                xorValues.emplace_back(currentXorValue);
                prevXorRow ^= matrix[row][column];
            }
        }
        const auto iterator = std::next(xorValues.begin(), k - 1);
        std::ranges::nth_element(xorValues, iterator, std::greater<int>());
        return *iterator;
    }
};

}

namespace FindKthLargestXORCoordinateValueTask
{

TEST(FindKthLargestXORCoordinateValueTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.kthLargestValue({{5, 2}, {1, 6}}, 1));
    ASSERT_EQ(5, solution.kthLargestValue({{5, 2}, {1, 6}}, 2));
    ASSERT_EQ(4, solution.kthLargestValue({{5, 2}, {1, 6}}, 3));
}

TEST(FindKthLargestXORCoordinateValueTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.kthLargestValue({{5, 2}, {1, 6}}, 4));
    ASSERT_EQ(1, solution.kthLargestValue({{10, 9, 5}, {2, 0, 4}, {1, 0, 9}, {3, 4, 8}}, 10));
}

}