#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findGCD(std::vector<int> const &nums) const
    {
        auto [minValue, maxValue] = std::ranges::minmax(nums);
        return std::gcd(minValue, maxValue);
    }
};

}

namespace FindGCDivisorOfArrayTask
{

TEST(FindGCDivisorOfArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findGCD({2, 5, 6, 9, 10}));
    ASSERT_EQ(1, solution.findGCD({7, 5, 6, 8, 3}));
    ASSERT_EQ(3, solution.findGCD({3, 3}));
}

}