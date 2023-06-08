#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countNegatives(std::vector<std::vector<int>> const &grid) const
    {
        const size_t columnCount = grid.front().size();
        size_t result = 0;
        size_t column = 0;
        for (auto row = grid.crbegin(); row != grid.crend(); ++row)
        {
            if (column == columnCount)
                break;
            while ((column < columnCount) && ((*row)[column] >= 0))
                ++column;
            result += (columnCount - column);
        }
        return static_cast<int>(result);
    }
};

}

namespace CountNegativeNumbersInSortedMatrixTask
{

TEST(CountNegativeNumbersInSortedMatrixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.countNegatives({{4, 3, 2, -1}, {3, 2, 1, -1}, {1, 1, -1, -2}, {-1, -1, -2, -3}}));
    ASSERT_EQ(0, solution.countNegatives({{3, 2}, {1, 0}}));
}

}