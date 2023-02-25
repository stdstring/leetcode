#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestRectangleArea(std::vector<int> const &heights) const
    {
        int maxArea = 0;
        std::stack<std::pair<size_t, int>> rectangleStarts;
        for (size_t index = 0; index < heights.size(); ++index)
        {
            size_t left = index;
            while (!rectangleStarts.empty() && (rectangleStarts.top().second > heights[index]))
            {
                maxArea = std::max(maxArea, rectangleStarts.top().second * static_cast<int>(index - rectangleStarts.top().first));
                left = rectangleStarts.top().first;
                rectangleStarts.pop();
            }
            rectangleStarts.emplace(left, heights[index]);
        }
        while (!rectangleStarts.empty())
        {
            maxArea = std::max(maxArea, rectangleStarts.top().second * static_cast<int>(heights.size() - rectangleStarts.top().first));
            rectangleStarts.pop();
        }
        return maxArea;
    }
};

}

namespace LargestRectangleInHistogramTask
{

TEST(LargestRectangleInHistogramTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(10, solution.largestRectangleArea({2, 1, 5, 6, 2, 3}));
    ASSERT_EQ(4, solution.largestRectangleArea({2, 4}));
}

}