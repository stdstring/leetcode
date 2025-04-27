#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countSubarrays(std::vector<int> const &nums) const
    {
        size_t result  = 0;
        for (size_t index = 0; index < nums.size() - 2; ++index)
        {
            const int sum13 = nums[index] + nums[index + 2];
            if (2 * sum13 == nums[index + 1])
                ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace CountSubarraysLength3WithConditionTask
{

TEST(CountSubarraysLength3WithConditionTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.countSubarrays({1, 2, 1, 4, 1}));
    ASSERT_EQ(0, solution.countSubarrays({1, 1, 1}));
}

}