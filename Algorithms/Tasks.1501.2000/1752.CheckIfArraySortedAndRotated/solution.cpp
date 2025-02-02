#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool check(std::vector<int> const &nums) const
    {
        // find start
        size_t start = 0;
        for (size_t index = 0; index < nums.size() - 1; ++index)
        {
            if (nums[index] > nums[index + 1])
            {
                start = index + 1;
                break;
            }
        }
        // check
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[(start + index - 1) % nums.size()] > nums[(start + index) % nums.size()])
                return false;
        }
        return true;
    }
};

}

namespace CheckIfArraySortedAndRotatedTask
{

TEST(CheckIfArraySortedAndRotatedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.check({3, 4, 5, 1, 2}));
    ASSERT_EQ(false, solution.check({2, 1, 3, 4}));
    ASSERT_EQ(true, solution.check({1, 2, 3}));
}

}