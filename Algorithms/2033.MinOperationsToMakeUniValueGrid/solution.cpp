#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<std::vector<int>> const &grid, int x) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<int> numbers(rowCount * columnCount, 0);
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                numbers[row * columnCount + column] = grid[row][column];
            }
        }
        const auto median = std::next(numbers.begin(), static_cast<long long>(numbers.size() / 2));
        std::nth_element(numbers.begin(), median, numbers.end());
        const int medianValue = *median;
        int result = 0;
        for (const int number : numbers)
        {
            const int diff = std::abs(number - medianValue);
            if ((diff % x) > 0)
                return -1;
            result += diff / x;
        }
        return result;
    }
};

}

namespace MinOperationsToMakeUniValueGridTask
{

TEST(MinOperationsToMakeUniValueGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minOperations({{2, 4}, {6, 8}}, 2));
    ASSERT_EQ(5, solution.minOperations({{1, 5}, {2, 3}}, 1));
    ASSERT_EQ(-1, solution.minOperations({{1, 2}, {3, 4}}, 2));
}

}