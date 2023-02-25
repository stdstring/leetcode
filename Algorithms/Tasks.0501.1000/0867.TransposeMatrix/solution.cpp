#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> const &matrix) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::vector<std::vector<int>> result(columnCount, std::vector<int>(rowCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                result[column][row] = matrix[row][column];
        }
        return result;
    }
};

}

namespace TransposeMatrixTask
{

TEST(TransposeMatrixTask, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 4, 7}, {2, 5, 8}, {3, 6, 9}}), solution.transpose({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 4}, {2, 5}, {3, 6}}), solution.transpose({{1, 2, 3}, {4, 5, 6}}));
}

}