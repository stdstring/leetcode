#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findMin(std::vector<int> const &nums) const
    {
        if (nums.size() == 1)
            return nums.back();
        if (nums.front() < nums.back())
            return nums.front();
        size_t left = 0;
        size_t right = nums.size() - 1;
        while ((right - left) > 1)
        {
            size_t middle = (right + left) / 2;
            if (nums[left] > nums[middle])
                right = middle;
            else
                left = middle;
        }
        return nums[right];
    }
};

}

namespace FindMinimumInRotatedSortedArrayTask
{

TEST(FindMinimumInRotatedSortedArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.findMin({3, 4, 5, 1, 2}));
    ASSERT_EQ(0, solution.findMin({4, 5, 6, 7, 0, 1, 2}));
}

}