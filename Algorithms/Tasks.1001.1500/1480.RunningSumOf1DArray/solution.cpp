#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> runningSum(std::vector<int> const &nums) const
    {
        std::vector<int> prefixes(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
            prefixes[index] = (index > 0 ? prefixes[index - 1] : 0) + nums[index];
        return prefixes;
    }
};

}

namespace RunningSumOf1DArrayTask
{

TEST(RunningSumOf1DArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 6, 10}), solution.runningSum({1, 2, 3, 4}));
    ASSERT_EQ(std::vector<int>({1, 2, 3, 4, 5}), solution.runningSum({1, 1, 1, 1, 1}));
    ASSERT_EQ(std::vector<int>({3, 4, 6, 16, 17}), solution.runningSum({3, 1, 2, 10, 1}));
}

}