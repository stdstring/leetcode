#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int kthSmallest(std::vector<std::vector<int>> const &matrix, int k) const
    {
        std::vector<int> result(matrix.size() * matrix.size(), 0);
        for (size_t row = 0; row < matrix.size(); ++row)
        {
            for (size_t column = 0; column < matrix.size(); ++column)
                result[row * matrix.size() + column] = matrix[row][column];
        }
        std::sort(result.begin(), result.end());
        return result[static_cast<size_t>(k) - 1];
    }
};

}

namespace KthSmallestElementInSortedMatrixTask
{

TEST(KthSmallestElementInSortedMatrixTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(13, solution.kthSmallest({{1, 5, 9}, {10, 11, 13}, {12, 13, 15}}, 8));
    ASSERT_EQ(-5, solution.kthSmallest({{-5}}, 1));
}

}