#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> reverseSubmatrix(std::vector<std::vector<int>> const &grid, int x, int y, int k) const
    {
        std::vector<std::vector<int>> result(grid);
        for (int row1 = x, row2 = x + k - 1; row1 < row2; ++row1, --row2)
        {
            for (int column = y; column < y + k; ++column)
                std::swap(result[row1][column], result[row2][column]);
        }
        return result;
    }
};

}

namespace FlipSquareSubmatrixVerticallyTask
{

TEST(FlipSquareSubmatrixVerticallyTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 3, 4}, {13, 14, 15, 8}, {9, 10, 11, 12}, {5, 6, 7, 16}}),
              solution.reverseSubmatrix({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}, 1, 0, 3));
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 4, 4, 2}, {2, 3, 2, 3}}),
              solution.reverseSubmatrix({{3, 4, 2, 3}, {2, 3, 4, 2}}, 0, 2, 2));
}

}