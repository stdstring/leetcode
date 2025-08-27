#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int areaOfMaxDiagonal(std::vector<std::vector<int>> const &dimensions) const
    {
        int maxDiagonalSquare = 0;
        int maxArea = 0;
        for (std::vector<int> const &rectangle : dimensions)
        {
            const int length = rectangle[0];
            const int width = rectangle[1];
            const int diagonalSquare = length * length + width * width;
            if (diagonalSquare >= maxDiagonalSquare)
            {
                maxArea = std::max((diagonalSquare > maxDiagonalSquare) ? 0 : maxArea, length * width);
                maxDiagonalSquare = diagonalSquare;
            }
        }
        return maxArea;
    }
};

}

namespace MaxAreaLongestDiagonalRectangleTask
{

TEST(MaxAreaLongestDiagonalRectangleTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(48, solution.areaOfMaxDiagonal({{9, 3}, {8, 6}}));
    ASSERT_EQ(12, solution.areaOfMaxDiagonal({{3, 4}, {4, 3}}));
}

TEST(MaxAreaLongestDiagonalRectangleTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(20, solution.areaOfMaxDiagonal({{6, 5}, {8, 6}, {2, 10}, {8, 1}, {9, 2}, {3, 5}, {3, 5}}));
}

}