#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> searchRange(std::vector<int> const &nums, int target) const
    {
        if (nums.empty())
            return {-1, -1};
        if (target < nums[0])
            return {-1, -1};
        if (target > nums.back())
            return {-1, -1};
        if (target == nums[0])
            return {0, static_cast<int>(findRightTargetIndex(nums, 0))};
        if (target == nums.back())
            return { static_cast<int>(findLeftTargetIndex(nums, nums.size() - 1)), static_cast<int>(nums.size() - 1)};
        const int anyTargetIndex = findAnyTargetIndex(nums, target);
        if (anyTargetIndex == - 1)
            return {-1, -1};
        return { static_cast<int>(findLeftTargetIndex(nums, anyTargetIndex)), static_cast<int>(findRightTargetIndex(nums, anyTargetIndex))};
    }

private:
    int findAnyTargetIndex(std::vector<int> const &nums, int target) const
    {
        size_t left = 0;
        size_t right = nums.size() - 1;
        while ((right - left) > 1)
        {
            const size_t middle = (left + right) / 2;
            if (nums[middle] == target)
                return static_cast<int>(middle);
            if (nums[middle] < target)
                left = middle;
            else
                right = middle;
        }
        if (nums[left] == target)
            return static_cast<int>(left);
        if (nums[right] == target)
            return static_cast<int>(right);
        return -1;
    }

    size_t findLeftTargetIndex(std::vector<int> const &nums, size_t targetIndex) const
    {
        const int target = nums[targetIndex];
        if (nums[0] == target)
            return 0;
        size_t left = 0;
        size_t right = targetIndex;
        while ((right - left) > 1)
        {
            const size_t middle = (left + right) / 2;
            if (nums[middle] == target)
                right = middle;
            else
                left = middle;
        }
        return nums[left] == target ? left : right;
    }

    size_t findRightTargetIndex(std::vector<int> const &nums, size_t targetIndex) const
    {
        const int target = nums[targetIndex];
        if (nums.back() == target)
            return nums.size() - 1;
        size_t left = targetIndex;
        size_t right = nums.size() - 1;
        while ((right - left) > 1)
        {
            const size_t middle = (left + right) / 2;
            if (nums[middle] == target)
                left = middle;
            else
                right = middle;
        }
        return nums[right] == target ? right : left;
    }
};

}

namespace FindFirstLastElementPosInSortedArrayTask
{

TEST(FindFirstLastElementPosInSortedArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({3, 4}), solution.searchRange({5, 7, 7, 8, 8, 10}, 8));
    ASSERT_EQ(std::vector<int>({-1, -1}), solution.searchRange({5, 7, 7, 8, 8, 10}, 6));
}

TEST(FindFirstLastElementPosInSortedArrayTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({-1, -1}), solution.searchRange({}, 0));
}

}