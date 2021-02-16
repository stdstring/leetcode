#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxProductPath(std::vector<std::vector<int>> const &grid) const
    {
        constexpr int modValue = 1000000007;
        std::vector<std::vector<long long>> minGridProduct;
        std::vector<std::vector<long long>> maxGridProduct;
        for (size_t row = 0; row < grid.size(); ++row)
        {
            minGridProduct.emplace_back();
            maxGridProduct.emplace_back();
            for (size_t column = 0; column < grid.front().size(); ++column)
            {
                if ((row == 0) && (column == 0))
                {
                    minGridProduct.back().push_back(grid[row][column]);
                    maxGridProduct.back().push_back(grid[row][column]);
                }
                if ((row == 0) && (column > 0))
                {
                    const long long rightStepValue1 = minGridProduct[row][column - 1] * grid[row][column];
                    const long long rightStepValue2 = maxGridProduct[row][column - 1] * grid[row][column];
                    minGridProduct.back().push_back(std::min(rightStepValue1, rightStepValue2));
                    maxGridProduct.back().push_back(std::max(rightStepValue1, rightStepValue2));
                }
                if ((row > 0) && (column == 0))
                {
                    const long long bottomStepValue1 = minGridProduct[row - 1][column] * grid[row][column];
                    const long long bottomStepValue2 = maxGridProduct[row - 1][column] * grid[row][column];
                    minGridProduct.back().push_back(std::min(bottomStepValue1, bottomStepValue2));
                    maxGridProduct.back().push_back(std::max(bottomStepValue1, bottomStepValue2));
                }
                if ((row > 0) && (column > 0))
                {
                    const long long bottomStepValue1 = minGridProduct[row - 1][column] * grid[row][column];
                    const long long bottomStepValue2 = maxGridProduct[row - 1][column] * grid[row][column];
                    const long long rightStepValue1 = minGridProduct[row][column - 1] * grid[row][column];
                    const long long rightStepValue2 = maxGridProduct[row][column - 1] * grid[row][column];
                    minGridProduct.back().push_back(std::min({ bottomStepValue1, bottomStepValue2, rightStepValue1, rightStepValue2}));
                    maxGridProduct.back().push_back(std::max({ bottomStepValue1, bottomStepValue2, rightStepValue1, rightStepValue2}));
                }
            }
        }
        return maxGridProduct.back().back() < 0 ? -1 : static_cast<int>(maxGridProduct.back().back() % modValue);
    }
};

}

namespace MaximumNonNegativeProductInMatrixTask
{

TEST(MaximumNonNegativeProductInMatrixTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(-1, solution.maxProductPath({{-1, -2, -3}, {-2, -3, -3}, {-3, -3, -2}}));
    ASSERT_EQ(8, solution.maxProductPath({{1, -2, 1}, {1, -2, 1}, {3, -4, 1}}));
    ASSERT_EQ(0, solution.maxProductPath({{1, 3}, {0, -4}}));
    ASSERT_EQ(2, solution.maxProductPath({{ 1, 4, 4, 0}, {-2, 0, 0, 1}, {1, -1, 1, 1}}));
}

TEST(MaximumNonNegativeProductInMatrixTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(19215865, solution.maxProductPath({{2, 1, 3, 0, -3, 3, -4, 4, 0, -4},
                                                 {-4, -3, 2, 2, 3, -3, 1, -1, 1, -2},
                                                 {-2, 0, -4, 2, 4, -3, -4, -1, 3, 4},
                                                 {-1, 0, 1, 0, -3, 3, -2, -3, 1, 0},
                                                 {0, -1, -2, 0, -3, -4, 0, 3, -2, -2},
                                                 {-4, -2, 0, -1, 0, -3, 0, 4, 0, -3},
                                                 {-3, -4, 2, 1, 0, -4, 2, -4, -1, -3},
                                                 {3, -2, 0, -4, 1, 0, 1, -3, -1, -1},
                                                 {3, -4, 0, 2, 0, -2, 2, -4, -2, 4},
                                                 {0, 4, 0, -3, -4, 3, 3, -1, -2, -2}}));
}

}