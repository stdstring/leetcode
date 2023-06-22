#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxStrength(std::vector<int> const &nums) const
    {
        if (nums.size() == 1)
            return nums.front();
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        long long result = 0;
        size_t current = 0;
        // process pairs of negative numbers
        for (;(current + 1) < numbers.size() && (numbers[current] < 0) && (numbers[current + 1] < 0); current += 2)
        {
            if (result == 0)
                result = 1;
            result *= numbers[current];
            result *= numbers[current + 1];
        }
        // process unpaired negative numbers
        if ((current < numbers.size()) && (numbers[current] < 0))
            ++current;
        // process zeroes
        while ((current < numbers.size()) && (numbers[current] == 0))
            ++current;
        // process positive numbers
        for (;(current < numbers.size()); ++current)
        {
            if (result == 0)
                result = 1;
            result *= numbers[current];
        }
        return result;
    }
};

}

namespace MaxStrengthOfGroupTask
{

TEST(MaxStrengthOfGroupTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1350, solution.maxStrength({3, -1, -5, 2, 5, -9}));
    ASSERT_EQ(20, solution.maxStrength({-4, -5, -4}));
}

TEST(MaxStrengthOfGroupTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(162, solution.maxStrength({9, 6, 3}));
    ASSERT_EQ(-9, solution.maxStrength({-9}));
}

}