#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSubarrayProductLessThanK(std::vector<int> const &nums, int k) const
    {
        if (k <= 1)
            return 0;
        size_t count = 0;
        int product = 1;
        size_t start = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            product *= nums[index];
            while (product >= k)
                product /= nums[start++];
            if (start <= index)
                count += (index - start + 1);
        }
        return static_cast<int>(count);
    }
};

}

namespace SubarrayProductLessThanKTask
{

TEST(SubarrayProductLessThanKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.numSubarrayProductLessThanK({10, 5, 2, 6}, 100));
    ASSERT_EQ(0, solution.numSubarrayProductLessThanK({1, 2, 3}, 0));
}

TEST(SubarrayProductLessThanKTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(31, solution.numSubarrayProductLessThanK({10, 2, 2, 5, 4, 4, 4, 3, 7, 7}, 289));
}

}