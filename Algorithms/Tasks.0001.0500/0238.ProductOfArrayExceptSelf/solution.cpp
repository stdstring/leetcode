#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> productExceptSelf(std::vector<int> const &nums) const
    {
        std::vector<int> result(nums.size(), 1);
        int prefix = nums[0];
        for (size_t index = 1; index < nums.size(); ++index)
        {
            result[index] *= prefix;
            prefix *= nums[index];
        }
        int suffix = nums[nums.size() - 1];
        for (size_t index = 1; index < nums.size(); ++index)
        {
            result[nums.size() - 1 - index] *= suffix;
            suffix *= nums[nums.size() - 1 - index];
        }
        return result;
    }
};

}

namespace ProductOfArrayExceptSelfTask
{

TEST(ProductOfArrayExceptSelfTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({24, 12, 8, 6}), solution.productExceptSelf({1, 2, 3, 4}));
    ASSERT_EQ(std::vector<int>({0, 0, 9, 0, 0}), solution.productExceptSelf({-1, 1, 0, -3, 3}));
}

}