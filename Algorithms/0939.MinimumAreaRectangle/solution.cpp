#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minAreaRect(std::vector<std::vector<int>> const &points) const
    {
        if (points.size() == 1)
            return 0;
        // sort point by X then by Y
        std::vector<std::vector<int>> sortedPoints(points);
        std::sort(sortedPoints.begin(), sortedPoints.end(), [](std::vector<int> const &left, std::vector<int> const &right){ return (left[0] < right[0]) || (left[0] == right[0] && left[1] < right[1]); });
        // create indices of point's group with the same X
        std::vector<size_t> xIndices;
        int currentX = INT_MIN;
        for (size_t index = 0; index < sortedPoints.size(); ++index)
        {
            if (currentX != sortedPoints[index][0])
                xIndices.push_back(index);
            currentX = sortedPoints[index][0];
        }
        // find min area
        int minArea = INT_MAX;
        for (size_t left = 0; left < xIndices.size() - 1; ++left)
        {
            const size_t leftFrom = xIndices[left];
            const size_t leftTo = xIndices[left + 1] - 1;
            if (leftFrom == leftTo)
                continue;
            const int leftX = sortedPoints[leftFrom][0];
            for (size_t right = left + 1; right < xIndices.size(); ++right)
            {
                const size_t rightFrom = xIndices[right];
                const size_t rightTo = (right + 1) < xIndices.size() ? xIndices[right + 1] - 1 : sortedPoints.size() - 1;
                if (rightFrom == rightTo)
                    continue;
                const int rightX = sortedPoints[rightFrom][0];
                size_t leftIndex = leftFrom;
                size_t rightIndex = rightFrom;
                int bottomY = INT_MIN;
                while (leftIndex <= leftTo && rightIndex <= rightTo)
                {
                    if (sortedPoints[leftIndex][1] < sortedPoints[rightIndex][1])
                        ++leftIndex;
                    else if (sortedPoints[leftIndex][1] > sortedPoints[rightIndex][1])
                        ++rightIndex;
                    else
                    {
                        if (bottomY != INT_MIN)
                            minArea = std::min(minArea, (rightX - leftX) * (sortedPoints[leftIndex][1] - bottomY));
                        bottomY = sortedPoints[leftIndex][1];
                        ++leftIndex;
                        ++rightIndex;
                    }
                }
            }
        }
        return minArea == INT_MAX ? 0 : minArea;
    }
};

}

namespace MinimumAreaRectangleTask
{

TEST(MinimumAreaRectangleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.minAreaRect({{1, 1}, {1, 3}, {3, 1}, {3, 3}, {2, 2}}));
    ASSERT_EQ(2, solution.minAreaRect({{1, 1}, {1, 3}, {3, 1}, {3, 3}, {4, 1}, {4, 3}}));
}

TEST(MinimumAreaRectangleTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.minAreaRect({{3, 2}, {3, 1}, {4, 4}, {1, 1}, {4, 3}, {0, 3}, {0, 2}, {4, 0}}));
}

}