#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int search(std::vector<int> const &nums, int target) const
    {
        if (nums.empty())
            return -1;
        if (nums.size() == 1)
            return nums[0] == target ? 0 : -1;
        if (nums[0] == target)
            return 0;
        if (nums.back() == target)
            return static_cast<int>(nums.size() - 1);
        size_t left = 0;
        size_t right = nums.size() - 1;
        while ((right - left) > 1)
        {
            const size_t middle = (left + right) / 2;
            if (nums[middle] == target)
                return static_cast<int>(middle);
            if (nums[left] < target && nums[middle] > target)
                right = middle;
            else if (nums[middle] < target && nums[right] > target)
                left = middle;
            else if (nums[left] > nums[middle])
                right = middle;
            else
                left = middle;
        }
        return nums[right] == target ? static_cast<int>(right) : -1;
    }
};

}

namespace SearchInRotatedSortedArrayTask
{

TEST(SearchInRotatedSortedArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.search({4, 5, 6, 7, 0, 1, 2}, 0));
    ASSERT_EQ(-1, solution.search({4, 5, 6, 7, 0, 1, 2}, 3));
    ASSERT_EQ(-1, solution.search({1}, 0));
}

TEST(SearchInRotatedSortedArrayTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(5, solution.search({4, 5, 6, 7, 0, 1, 2}, 1));
    ASSERT_EQ(4, solution.search({4, 5, 6, 7, 8, 1, 2, 3}, 8));
}

}