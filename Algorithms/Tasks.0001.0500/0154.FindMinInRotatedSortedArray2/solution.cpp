#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findMin(std::vector<int> const &nums) const
    {
        return std::ranges::min(nums);
    }
};

}

namespace FindMinInRotatedSortedArray2Task
{

TEST(FindMinInRotatedSortedArray2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.findMin({1, 3, 5}));
    ASSERT_EQ(0, solution.findMin({2, 2, 2, 0, 1}));
}

}