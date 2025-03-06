#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findMissingAndRepeatedValues(std::vector<std::vector<int>> const &grid) const
    {
        const size_t n = grid.size();
        std::vector<int> numbers(n * n, 0);
        for (std::vector<int> const &row : grid)
        {
            for (int number : row)
                ++numbers[number - 1];
        }
        std::vector<int> result(2, 0);
        for (size_t number = 1; number <= n * n; ++number)
        {
            if (numbers[number - 1] == 2)
                result[0] = static_cast<int>(number);
            if (numbers[number - 1] == 0)
                result[1] = static_cast<int>(number);
        }
        return result;
    }
};

}

namespace FindMissingRepeatedValuesTask
{

TEST(FindMissingRepeatedValuesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 4}), solution.findMissingAndRepeatedValues({{1, 3}, {2, 2}}));
    ASSERT_EQ(std::vector<int>({9, 5}), solution.findMissingAndRepeatedValues({{9, 1, 7}, {8, 9, 2}, {3, 4, 6}}));
}

}