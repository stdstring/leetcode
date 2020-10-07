#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int singleNonDuplicate(std::vector<int> const &nums) const
    {
        if (nums.size() == 1)
            return nums.front();
        size_t left = 0;
        size_t right = nums.size() - 1;
        while ((right - left) > 1)
        {
            size_t middle = (right + left) / 2;
            if (middle % 2 == 0)
                --middle;
            if (nums[middle] == nums[middle - 1])
                left = middle + 1;
            else if (nums[middle] == nums[middle + 1])
                right = middle - 1;
            else
                return nums[middle];
        }
        return nums[right];
    }
};

}

namespace SingleElementInSortedArrayTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.singleNonDuplicate({1, 1, 2, 3, 3, 4, 4, 8, 8}));
    ASSERT_EQ(10, solution.singleNonDuplicate({3, 3, 7, 7, 10, 11, 11}));
}

}