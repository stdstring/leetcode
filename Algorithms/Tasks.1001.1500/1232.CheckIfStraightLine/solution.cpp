#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkStraightLine(std::vector<std::vector<int>> const &coordinates) const
    {
        const int x0 = coordinates[0][0];
        const int y0 = coordinates[0][1];
        const int directionX = coordinates[1][0] - x0;
        const int directionY = coordinates[1][1] - y0;
        for (size_t index = 2; index < coordinates.size(); ++index)
        {
            const int currentX = coordinates[index][0] - x0;
            const int currentY = coordinates[index][1] - y0;
            if (currentX * directionY != currentY * directionX)
                return false;
        }
        return true;
    }
};

}

namespace CheckIfStraightLineTask
{

TEST(CheckIfStraightLineTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.checkStraightLine({{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}}));
    ASSERT_EQ(false, solution.checkStraightLine({{1, 1}, {2, 2}, {3, 4}, {4, 5}, {5, 6}, {7, 7}}));
}

}