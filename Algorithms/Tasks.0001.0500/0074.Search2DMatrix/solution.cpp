#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool searchMatrix(std::vector<std::vector<int>> const &matrix, int target) const
    {
        if ((target < matrix.front().front()) || (target > matrix.back().back()))
            return false;
        if ((target == matrix.front().front()) || (target == matrix.back().back()))
            return true;
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        const size_t cellCount = rowCount * columnCount;
        size_t left = 0;
        size_t right = cellCount - 1;
        while (left <= right)
        {
            const size_t middle = (left + right) / 2;
            const int value = matrix[middle / columnCount][middle % columnCount];
            if (target == value)
                return true;
            if (target > value)
                left = middle + 1;
            else
                right = middle - 1;
        }
        return false;
    }
};

}

namespace Search2DMatrixTask
{

TEST(Search2DMatrixTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.searchMatrix({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}}, 3));
    ASSERT_EQ(false, solution.searchMatrix({{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}}, 13));
}

TEST(Search2DMatrixTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.searchMatrix({{1}}, 0));
    ASSERT_EQ(true, solution.searchMatrix({{1}}, 1));
}

}