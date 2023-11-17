#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minPairSum(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        int result = INT_MIN;
        for (size_t shift = 0; shift < numbers.size() / 2; ++shift)
            result = std::max(result, numbers[shift] + numbers[numbers.size() - 1 - shift]);
        return result;
    }
};

}

namespace MinMaxPairSumInArrayTask
{

TEST(MinMaxPairSumInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.minPairSum({3, 5, 2, 3}));
    ASSERT_EQ(8, solution.minPairSum({3, 5, 4, 2, 4, 6}));
}

}