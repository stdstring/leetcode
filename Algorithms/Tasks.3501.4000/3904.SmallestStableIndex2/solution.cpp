#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int firstStableIndex(std::vector<int> const &nums, int k) const
    {
        std::vector<int> rlMinValues(nums.size(), 0);
        for (size_t rIndex = 0; rIndex < nums.size(); ++rIndex)
        {
            const size_t index = nums.size() - 1 - rIndex;
            rlMinValues[index] = std::min(nums[index], rIndex == 0 ? INT_MAX : rlMinValues[index + 1]);
        }
        int maxValue = INT_MIN;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            maxValue = std::max(maxValue, nums[index]);
            const int delta = maxValue - rlMinValues[index];
            if (delta <= k)
                return static_cast<int>(index);
        }
        return -1;
    }
};

}

namespace SmallestStableIndex2Task
{

TEST(SmallestStableIndex2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.firstStableIndex({5, 0, 1, 4}, 3));
    ASSERT_EQ(-1, solution.firstStableIndex({3, 2, 1}, 1));
    ASSERT_EQ(0, solution.firstStableIndex({0}, 0));
}

}