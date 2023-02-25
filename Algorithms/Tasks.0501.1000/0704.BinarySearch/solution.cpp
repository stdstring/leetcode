#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int search(std::vector<int> const &nums, int target) const
    {
        if ((target < nums.front()) || (target > nums.back()))
            return -1;
        size_t left = 0;
        size_t right = nums.size() - 1;
        while (left < right)
        {
            const size_t middle = (left + right) / 2;
            if (nums[middle] == target)
                return static_cast<int>(middle);
            if (nums[middle] < target)
                left = middle + 1;
            else
                right = middle - 1;
        }
        return nums[left] == target ? static_cast<int>(left) : -1;
    }
};

}

namespace BinarySearchTask
{

TEST(BinarySearchTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.search({-1, 0, 3, 5, 9, 12}, 9));
    ASSERT_EQ(-1, solution.search({-1, 0, 3, 5, 9, 12}, 2));
}

}