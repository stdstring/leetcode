#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int searchInsert(std::vector<int> const &nums, int target) const
    {
        if (nums.empty())
            return 0;
        if (target <= nums[0])
            return 0;
        if (target == nums.back())
            return nums.size() - 1;
        if (target > nums.back())
            return nums.size();
        int left = 0;
        int right = nums.size() - 1;
        while (right - left > 1)
        {
            int middle = (right + left) / 2;
            if (nums[middle] == target)
                return middle;
            else if (nums[middle] < target)
                left = middle;
            else if (nums[middle] > target)
                right = middle;
        }
        return right;
    }
};

}

namespace SearchInsertPositionTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.searchInsert({1, 3, 5, 6}, 5));
    ASSERT_EQ(1, solution.searchInsert({1, 3, 5, 6}, 2));
    ASSERT_EQ(4, solution.searchInsert({1, 3, 5, 6}, 7));
    ASSERT_EQ(0, solution.searchInsert({1, 3, 5, 6}, 0));
}

}