#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long gcdSum(std::vector<int> const &nums) const
    {
        std::vector<int> prefixGcd(nums.size(), 0);
        int maxValue = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            maxValue = std::max(maxValue, nums[index]);
            prefixGcd[index] = std::gcd(maxValue, nums[index]);
        }
        std::ranges::sort(prefixGcd);
        long long result = 0;
        for (size_t left = 0, right = prefixGcd.size() - 1; left < right; ++left, --right)
            result += std::gcd(prefixGcd[left], prefixGcd[right]);
        return result;
    }
};

}

namespace TwoSumTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.gcdSum({2, 6, 4}));
    ASSERT_EQ(5, solution.gcdSum({3, 6, 2, 8}));
}

TEST(TwoSumTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.gcdSum({2}));
}

}