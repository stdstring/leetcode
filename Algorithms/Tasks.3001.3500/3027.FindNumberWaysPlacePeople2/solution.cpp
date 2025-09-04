#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfPairs(std::vector<std::vector<int>> const &points) const
    {
        std::vector<std::vector<int>> sortedPoints(points);
        auto cmp = [](std::vector<int> const &left, std::vector<int> const &right)
        {
            const int x1 = left[0];
            const int y1 = left[1];
            const int x2 = right[0];
            const int y2 = right[1];
            return (x1 < x2) || ((x1 == x2) && (y2 < y1));
        };
        std::ranges::sort(sortedPoints, cmp);
        size_t result = 0;
        // Alice - upper left corner, Bob - lower right corner
        for (size_t startIndex = 0; startIndex < sortedPoints.size(); ++startIndex)
        {
            int y1 = sortedPoints[startIndex][1];
            int y2Min = INT_MIN;
            for (size_t endIndex = startIndex + 1; endIndex < sortedPoints.size(); ++endIndex)
            {
                int y2 = sortedPoints[endIndex][1];
                if (y2 > y1)
                    continue;
                if (y2 <= y2Min)
                    continue;
                y2Min = y2;
                ++result;
            }
        }
        return static_cast<int>(result);
    }
};

}

namespace FindNumberWaysPlacePeople2Task
{

TEST(FindNumberWaysPlacePeople2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.numberOfPairs({{1, 1}, {2, 2}, {3, 3}}));
    ASSERT_EQ(2, solution.numberOfPairs({{6, 2}, {4, 4}, {2, 6}}));
    ASSERT_EQ(2, solution.numberOfPairs({{3, 1}, {1, 3}, {1, 1}}));
}

}