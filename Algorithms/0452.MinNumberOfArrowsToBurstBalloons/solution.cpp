#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findMinArrowShots(std::vector<std::vector<int>> const &points) const
    {
        std::vector<std::vector<int>> balloons(points);
        std::sort(balloons.begin(), balloons.end(), [](std::vector<int> const &l, std::vector<int> const &r){ return (l[1] < r[1]); });
        size_t shotsCount = 0;
        int portionFinish = balloons[0][1];
        for (size_t index = 1; index < balloons.size(); ++index)
        {
            if (balloons[index][0] > portionFinish)
            {
                ++shotsCount;
                portionFinish = balloons[index][1];
            }
        }
        ++shotsCount;
        return static_cast<int>(shotsCount);
    }
};

}

namespace MinNumberOfArrowsToBurstBalloonsTask
{

TEST(MinNumberOfArrowsToBurstBalloonsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findMinArrowShots({{10, 16}, {2, 8}, {1, 6}, {7, 12}}));
    ASSERT_EQ(4, solution.findMinArrowShots({{1, 2}, {3, 4}, {5, 6}, {7, 8}}));
    ASSERT_EQ(2, solution.findMinArrowShots({{1, 2}, {2, 3}, {3, 4}, {4, 5}}));
}

TEST(MinNumberOfArrowsToBurstBalloonsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findMinArrowShots({{3, 9}, {7, 12}, {3, 8}, {6, 8}, {9, 10}, {2, 9}, {0, 9}, {3, 9}, {0, 6}, {2, 8}}));
    ASSERT_EQ(2, solution.findMinArrowShots({{9, 12}, {1, 10}, {4, 11}, {8, 12}, {3, 9}, {6, 9}, {6, 7}}));
}


}