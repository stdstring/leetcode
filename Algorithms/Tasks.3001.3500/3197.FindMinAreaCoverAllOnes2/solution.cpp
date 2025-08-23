#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumSum(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        size_t bestSum = INT_MAX;
        // row cut
        for (size_t cut = 0; cut < rowCount - 1; ++cut)
        {
            const size_t minAreaTop = calcMinArea(grid, 0, 0, columnCount - 1, cut);
            const size_t minAreaBottom = calcMinArea(grid, 0, cut + 1, columnCount - 1, rowCount - 1);
            if ((minAreaTop == 0) || (minAreaBottom == 0))
                continue;
            const size_t minAreaRestTop = processSecondCut(grid, 0, 0, columnCount - 1, cut);
            const size_t minAreaRestBottom = processSecondCut(grid, 0, cut + 1, columnCount - 1, rowCount - 1);
            if (minAreaRestBottom > 0)
                bestSum = std::min(bestSum, minAreaTop + minAreaRestBottom);
            if (minAreaRestTop > 0)
                bestSum = std::min(bestSum, minAreaBottom + minAreaRestTop);
        }
        // column cut
        for (size_t cut = 0; cut < columnCount - 1; ++cut)
        {
            const size_t minAreaLeft = calcMinArea(grid, 0, 0, cut, rowCount - 1);
            const size_t minAreaRight = calcMinArea(grid, cut + 1, 0, columnCount -1, rowCount - 1);
            if ((minAreaLeft == 0) || (minAreaRight == 0))
                continue;
            const size_t minAreaRestLeft = processSecondCut(grid, 0, 0, cut, rowCount - 1);
            const size_t minAreaRestRight = processSecondCut(grid, cut + 1, 0, columnCount - 1, rowCount - 1);
            if (minAreaRestRight > 0)
                bestSum = std::min(bestSum, minAreaLeft + minAreaRestRight);
            if (minAreaRestLeft > 0)
                bestSum = std::min(bestSum, minAreaRight + minAreaRestLeft);
        }
        return static_cast<int>(bestSum);
    }

private:
    [[nodiscard]] size_t processSecondCut(std::vector<std::vector<int>> const &grid, size_t left, size_t top, size_t right, size_t bottom) const
    {
        size_t bestSum = INT_MAX;
        // row cut
        for (size_t cut = top; cut < bottom; ++cut)
        {
            const size_t minAreaTop = calcMinArea(grid, left, top, right, cut);
            const size_t minAreaBottom = calcMinArea(grid, left, cut + 1, right, bottom);
            if ((minAreaTop > 0) && (minAreaBottom > 0))
                bestSum = std::min(bestSum, minAreaTop + minAreaBottom);
        }
        // column cut
        for (size_t cut = left; cut < right; ++cut)
        {
            const size_t minAreaLeft = calcMinArea(grid, left, top, cut, bottom);
            const size_t minAreaRight = calcMinArea(grid, cut + 1, top, right, bottom);
            if ((minAreaLeft > 0) && (minAreaRight > 0))
                bestSum = std::min(bestSum, minAreaLeft + minAreaRight);
        }
        return (bestSum == INT_MAX) ? 0 : bestSum;
    }

    [[nodiscard]] size_t calcMinArea(std::vector<std::vector<int>> const &grid, size_t left, size_t top, size_t right, size_t bottom) const
    {
        size_t areaLeft = INT_MAX;
        size_t areaTop = INT_MAX;
        size_t areaRight = 0;
        size_t areaBottom = 0;
        for (size_t row = top; row <= bottom; ++row)
        {
            for (size_t column = left; column <= right; ++column)
            {
                if (grid[row][column] == 1)
                {
                    areaLeft = std::min(areaLeft, column);
                    areaTop = std::min(areaTop, row);
                    areaRight = std::max(areaRight, column); // NOLINT(readability-suspicious-call-argument)
                    areaBottom = std::max(areaBottom, row);
                }
            }
        }
        return (areaLeft == INT_MAX) ? 0 : (areaRight - areaLeft + 1) * (areaBottom - areaTop + 1);
    }
};

}

namespace FindMinAreaCoverAllOnes2Task
{

TEST(FindMinAreaCoverAllOnes2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minimumSum({{1, 0, 1}, {1, 1, 1}}));
    ASSERT_EQ(5, solution.minimumSum({{1, 0, 1, 0}, {0, 1, 0, 1}}));
}

}