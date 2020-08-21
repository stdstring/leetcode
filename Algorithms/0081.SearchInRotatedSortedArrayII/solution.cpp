#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool search(std::vector<int> const &nums, int target) const
    {
        if (nums.empty())
            return false;
        if (nums.size() == 1)
            return nums[0] == target;
        if (nums[0] == target)
            return true;
        if (nums.back() == target)
            return true;
        return searchImpl(nums, target, 0, nums.size() - 1);
    }

private:
    bool searchImpl(std::vector<int> const &nums, int target, size_t left, size_t right) const
    {
        if ((right - left) <= 1)
            return  nums[right] == target;
        const size_t middle = (left + right) / 2;
        if (nums[middle] == target)
            return true;
        if (nums[left] < target && nums[middle] > target)
            return searchImpl(nums, target, left, middle);
        if (nums[middle] < target && nums[right] > target)
            return searchImpl(nums, target, middle, right);
        if (nums[left] > nums[middle])
            return searchImpl(nums, target, left, middle);
        if (nums[middle] > nums[right])
            return searchImpl(nums, target, middle, right);
        // check both [left, middle] & [middle, right] ranges
        if (searchImpl(nums, target, left, middle))
            return true;
        return searchImpl(nums, target, middle, right);
    }
};

}

namespace SearchInRotatedSortedArrayIITask
{

TEST(SearchInRotatedSortedArrayIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.search({2, 5, 6, 0, 0, 1, 2}, 0));
    ASSERT_EQ(false, solution.search({2, 5, 6, 0, 0, 1, 2}, 3));
}

TEST(SearchInRotatedSortedArrayIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.search({1, 3, 1, 1, 1}, 3));
}

}