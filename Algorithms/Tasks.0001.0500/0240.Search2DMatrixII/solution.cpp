#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool searchMatrixViaBinarySearch(std::vector<std::vector<int>> const &matrix, int target) const
    {
        const auto rowRangeStart = std::partition_point(matrix.cbegin(), matrix.cend(), [target](std::vector<int> const &row){ return row.back() < target; });
        const auto rowRangeEnd = std::partition_point(rowRangeStart, matrix.cend(), [target](std::vector<int> const &row){ return row.front() <= target; });
        return std::any_of(rowRangeStart, rowRangeEnd, [target](std::vector<int> const &row){ return std::binary_search(row.cbegin(), row.cend(), target); });
    }

    [[nodiscard]] bool searchMatrixViaTraverse(std::vector<std::vector<int>> const &matrix, int target) const
    {
        // As the rows are sorted->matrix[i][j] < matrix[i][j + 1]
        // As the columns are sorted->matrix[i][j] >matrix[i - 1][j]
        // Hence it can be said that :
        // 1) any element right to matrix[i][j] will be greater than it.
        // 2) any element to the top of matrix[i][j] will be less than it.
        // So we start searching from BOTTOM_LEFT :
        // 1) if element found -> return TRUE
        // 2) if matrix[i][j] > target->move UP.
        // 3) if matrix[i][j] < target->move RIGHT.
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        size_t row = 0;
        size_t column = 0;
        while ((row < rowCount) && (column < columnCount))
        {
            const int current = matrix[rowCount - 1 - row][column];
            if (current == target)
                return true;
            if (target < current)
                ++row;
            else
                ++column;
        }
        return false;
    }
};

}

namespace
{

void checkSearchMatrix(std::vector<std::vector<int>> const &matrix, int target, bool expectedResult)
{
    constexpr Solution solution;
    ASSERT_EQ(expectedResult, solution.searchMatrixViaBinarySearch(matrix, target));
    ASSERT_EQ(expectedResult, solution.searchMatrixViaTraverse(matrix, target));
}

}

namespace Search2DMatrixIITask
{

TEST(Search2DMatrixIITaskTests, Examples)
{
    checkSearchMatrix({{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}, 5, true);
    checkSearchMatrix({{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}, 20, false);
}

TEST(Search2DMatrixIITaskTests, FromWrongAnswers)
{
    checkSearchMatrix({{-5}}, - 5, true);
}

}