#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> divideArray(std::vector<int> const &nums, int k) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        std::vector<std::vector<int>> result;
        for (size_t index = 0; index < numbers.size(); index += 3)
        {
            const int number0 = numbers[index];
            const int number1 = numbers[index + 1];
            const int number2 = numbers[index + 2];
            if ((number2 - number0) > k)
                return {};
            result.emplace_back(std::vector<int>({number0, number1, number2}));
        }
        return result;
    }
};

}

namespace DivideArrayIntoArraysWithMaxDiffTask
{

TEST(DivideArrayIntoArraysWithMaxDiffTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1, 3}, {3, 4, 5}, {7, 8, 9}}),
              solution.divideArray({1, 3, 4, 8, 7, 9, 3, 5, 1}, 2));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.divideArray({1, 3, 3, 2, 7, 3}, 3));
}

}