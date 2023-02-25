#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int furthestBuilding(std::vector<int> const &heights, int bricks, int ladders) const
    {
        std::priority_queue<int, std::vector<int>, std::greater<>> queue;
        for (size_t index = 1; index < heights.size(); ++index)
        {
            int diff = heights[index] - heights[index - 1];
            if (diff <= 0)
                continue;
            if (ladders > 0)
            {
                queue.push(diff);
                --ladders;
            }
            else if (!queue.empty() && (diff > queue.top()))
            {
                queue.push(diff);
                bricks -= queue.top();
                queue.pop();
            }
            else
                bricks -= diff;
            if (bricks < 0)
                return static_cast<int>(index - 1);
        }
        return static_cast<int>(heights.size() - 1);
    }
};

}

namespace FurthestBuildingYouCanReachTask
{

TEST(FurthestBuildingYouCanReachTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.furthestBuilding({4, 2, 7, 6, 9, 14, 12}, 5, 1));
    ASSERT_EQ(7, solution.furthestBuilding({4, 12, 2, 7, 3, 18, 20, 3, 19}, 10, 2));
    ASSERT_EQ(3, solution.furthestBuilding({14, 3, 19, 3}, 17, 0));
}

TEST(FurthestBuildingYouCanReachTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.furthestBuilding({1, 5, 1, 2, 3, 4, 10000}, 4, 1));
    ASSERT_EQ(7, solution.furthestBuilding({1, 13, 1, 1, 13, 5, 11, 11}, 10, 8));
}

}