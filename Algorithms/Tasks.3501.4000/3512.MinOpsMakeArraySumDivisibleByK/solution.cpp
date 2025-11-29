#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<int> const &nums, int k) const
    {
        const int sum = std::accumulate(nums.begin(), nums.end(), 0);
        return sum % k;
    }
};

}

namespace MinOpsMakeArraySumDivisibleByKTask
{

TEST(MinOpsMakeArraySumDivisibleByKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minOperations({3, 9, 7}, 5));
    ASSERT_EQ(0, solution.minOperations({4, 1, 3}, 4));
    ASSERT_EQ(5, solution.minOperations({3, 2}, 6));
}

}