#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long largestSquareArea(std::vector<std::vector<int>> const &bottomLeft, std::vector<std::vector<int>> const &topRight) const
    {
        const size_t rectangleCount = bottomLeft.size();
        long long maxArea = 0;
        for (size_t index1 = 0; index1 < rectangleCount; ++index1)
        {
            for (size_t index2 = index1 + 1; index2 < rectangleCount; ++index2)
            {
                auto [xSize, ySize] = calcIntersectionSize(bottomLeft[index1], topRight[index1], bottomLeft[index2], topRight[index2]);
                const int minSize = std::min(xSize, ySize);
                maxArea = std::max(maxArea, 1LL * minSize * minSize);
            }
        }
        return maxArea;
    }

private:
    [[nodiscard]] std::pair<int, int> calcIntersectionSize(std::vector<int> const &bottomLeft1,
                                                           std::vector<int> const &topRight1,
                                                           std::vector<int> const &bottomLeft2,
                                                           std::vector<int> const &topRight2) const
    {
        const int xl1 = bottomLeft1[0];
        const int xr1 = topRight1[0];
        const int xl2 = bottomLeft2[0];
        const int xr2 = topRight2[0];
        const int yb1 = bottomLeft1[1];
        const int yt1 = topRight1[1];
        const int yb2 = bottomLeft2[1];
        const int yt2 = topRight2[1];
        const bool isNotIntersect = (xl1 > xr2) || (xl2 > xr1) || (yb1 > yt2) || (yb2 > yt1);
        if (isNotIntersect)
            return std::pair<int, int>(0, 0);
        int xSize = std::min(xr1, xr2) - std::max(xl1, xl2);
        int ySize = std::min(yt1, yt2) - std::max(yb1, yb2);
        return std::pair<int, int>(xSize, ySize);
    }
};

}

namespace FindMaxSquareAreaInside2RectanglesTask
{

TEST(FindMaxSquareAreaInside2RectanglesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.largestSquareArea({{1, 1}, {2, 2}, {3, 1}}, {{3, 3}, {4, 4}, {6, 6}}));
    ASSERT_EQ(1, solution.largestSquareArea({{1, 1}, {2, 2}, {1, 2}}, {{3, 3}, {4, 4}, {3, 4}}));
    ASSERT_EQ(0, solution.largestSquareArea({{1, 1}, {3, 3}, {3, 1}}, {{2, 2}, {4, 4}, {4, 2}}));
}

TEST(FindMaxSquareAreaInside2RectanglesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.largestSquareArea({{1, 2}, {1, 2}}, {{4, 5}, {2, 3}}));
    ASSERT_EQ(1, solution.largestSquareArea({{2, 2}, {1, 3}}, {{3, 4}, {5, 5}}));
}

}