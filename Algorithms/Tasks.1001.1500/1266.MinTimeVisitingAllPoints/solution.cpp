#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minTimeToVisitAllPoints(std::vector<std::vector<int>> const &points) const
    {
        int time = 0;
        for (size_t index = 1; index < points.size(); ++index)
        {
            int deltaX = std::abs(points[index][0] - points[index - 1][0]);
            int deltaY = std::abs(points[index][1] - points[index - 1][1]);
            time += std::max(deltaX, deltaY);
        }
        return time;
    }
};

}

namespace MinTimeVisitingAllPointsTask
{

TEST(MinTimeVisitingAllPointsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.minTimeToVisitAllPoints({{1, 1}, {3, 4}, {-1, 0}}));
    ASSERT_EQ(5, solution.minTimeToVisitAllPoints({{3, 2}, {-2, 2}}));
}

}