#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int getMinDistance(std::vector<int> const &nums, int target, int start) const
    {
        const size_t startIndex = start;
        size_t minDistance = nums.size();
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (nums[index] == target)
            {
                minDistance = std::min(minDistance, index < startIndex ? startIndex - index : index - startIndex);
            }
        }
        return static_cast<int>(minDistance);
    }
};

}

namespace MinDistanceToTargetElementTask
{

TEST(MinDistanceToTargetElementTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.getMinDistance({1, 2, 3, 4, 5}, 5, 3));
    ASSERT_EQ(0, solution.getMinDistance({1}, 1, 0));
    ASSERT_EQ(0, solution.getMinDistance({1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1, 0));
}

}