#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxArea(std::vector<int> const &height) const
    {
        int maxArea = 0;
        size_t left = 0;
        size_t right = height.size() - 1;
        while (left < right)
        {
            int currentArea = (right - left) * std::min(height[right], height[left]);
            maxArea = std::max(maxArea, currentArea);
            if (height[left] < height[right])
                ++left;
            else
                --right;
        }
        return maxArea;
    }
};

}

namespace ContainerWithMostWaterTask
{

TEST(ContainerWithMostWaterTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(49, solution.maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}));
    ASSERT_EQ(1, solution.maxArea({1, 1}));
    ASSERT_EQ(16, solution.maxArea({4, 3, 2, 1, 4}));
    ASSERT_EQ(2, solution.maxArea({1, 2, 1}));
}

}