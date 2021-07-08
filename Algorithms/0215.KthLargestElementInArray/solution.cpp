#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findKthLargest(std::vector<int> const &nums, int k) const
    {
        std::vector<int> result(nums);
        std::sort(result.begin(), result.end());
        return result[nums.size() - k];
    }
};

}

namespace KthLargestElementInArrayTask
{

TEST(KthLargestElementInArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.findKthLargest({3, 2, 1, 5, 6, 4}, 2));
    ASSERT_EQ(4, solution.findKthLargest({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4));
}

}