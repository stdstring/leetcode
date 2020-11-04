#include <tuple>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool searchMatrix(std::vector<std::vector<int>> const &matrix, int target) const
    {
        if (matrix.empty())
            return false;
        if (matrix.front().empty())
            return false;
        if (matrix.front().front() > target)
            return false;
        if (matrix.back().back() < target)
            return false;
        // search row
        bool searchRowResult;
        size_t rowIndex;
        std::tie(searchRowResult, rowIndex) = searchRow(matrix, target);
        if (!searchRowResult)
            return false;
        // search value
        return searchValue(matrix[rowIndex], target);
    }

private:
    std::tuple<bool, size_t> searchRow(std::vector<std::vector<int>> const &matrix, int target) const
    {
        if (matrix.front().front() <= target && target <= matrix.front().back())
            return std::make_tuple(true, 0);
        if (matrix.back().front() <= target && target <= matrix.back().back())
            return std::make_tuple(true, matrix.size() - 1);
        size_t left = 0;
        size_t right = matrix.size() - 1;
        while ((right - left) > 1)
        {
            const size_t middle = (left + right) / 2;
            if (matrix[middle].front() <= target && target <= matrix[middle].back())
                return std::make_tuple(true, middle);
            if (target < matrix[middle].front())
                right = middle;
            else
                left = middle;
        }
        if (matrix[left].front() <= target && target <= matrix[left].back())
            return std::make_tuple(true, left);
        if (matrix[right].front() <= target && target <= matrix[right].back())
            return std::make_tuple(true, right);
        return std::make_tuple(false, 0);
    }

    bool searchValue(std::vector<int> const &row, int target) const
    {
        if (row.front() == target)
            return true;
        if (row.back() == target)
            return true;
        size_t left = 0;
        size_t right = row.size() - 1;
        while ((right - left) > 1)
        {
            const size_t middle = (left + right) / 2;
            if (row[middle] == target)
                return true;
            if (target < row[middle])
                right = middle;
            else
                left = middle;
        }
        return row[left] == target || row[right] == target;
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
    ASSERT_EQ(false, solution.searchMatrix({}, 0));
    ASSERT_EQ(false, solution.searchMatrix({{}}, 1));
}

}