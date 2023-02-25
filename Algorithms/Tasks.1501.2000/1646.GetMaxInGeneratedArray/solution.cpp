#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int getMaximumGenerated(int n) const
    {
        if (n == 0)
            return 0;
        const size_t maxNumber = n;
        std::vector<int> nums(maxNumber + 1, 0);
        nums[0] = 0;
        nums[1] = 1;
        for (size_t index = 1; 2 * index <= maxNumber; ++index)
        {
            nums[2 * index] = nums[index];
            if ((2 * index + 1) <= maxNumber)
                nums[2 * index + 1] = nums[index] + nums[index + 1];
        }
        return *std::max_element(nums.cbegin(), nums.cend());
    }
};

}

namespace GetMaxInGeneratedArrayTask
{

TEST(GetMaxInGeneratedArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.getMaximumGenerated(7));
    ASSERT_EQ(1, solution.getMaximumGenerated(2));
    ASSERT_EQ(2, solution.getMaximumGenerated(3));
    ASSERT_EQ(1, solution.getMaximumGenerated(1));
    ASSERT_EQ(0, solution.getMaximumGenerated(0));
}

}