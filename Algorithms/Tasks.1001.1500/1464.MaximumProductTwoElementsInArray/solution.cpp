#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxProduct(std::vector<int> const &nums) const
    {
        int first = std::max(nums[0], nums[1]);
        int second = std::min(nums[0], nums[1]);
        for (size_t index = 2; index < nums.size(); ++index)
        {
            const int current = nums[index];
            if (current >= first)
            {
                second = first;
                first = current;
            }
            else if (current > second)
                second = current;
        }
        return (first - 1) * (second - 1);
    }
};

}

namespace MaximumProductTwoElementsInArrayTask
{

TEST(MaximumProductTwoElementsInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.maxProduct({3, 4, 5, 2}));
    ASSERT_EQ(16, solution.maxProduct({1, 5, 4, 5}));
    ASSERT_EQ(12, solution.maxProduct({3, 7}));
}

}