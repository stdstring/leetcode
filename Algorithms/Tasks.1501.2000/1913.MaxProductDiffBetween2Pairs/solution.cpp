#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxProductDifference(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        return numbers[numbers.size() - 1] * numbers[numbers.size() - 2] - numbers[0] * numbers[1];
    }
};

}

namespace MaxProductDiffBetween2PairsTask
{

TEST(MaxProductDiffBetween2PairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(34, solution.maxProductDifference({5, 6, 2, 7, 4}));
    ASSERT_EQ(64, solution.maxProductDifference({4, 2, 5, 9, 7, 4, 8}));
}

}