#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkValidCuts(int n, std::vector<std::vector<int>> const &rectangles) const
    {
        std::vector<TRange> xRanges;
        xRanges.reserve(rectangles.size());
        std::vector<TRange> yRanges;
        yRanges.reserve(rectangles.size());
        for (std::vector<int> const &rectangle : rectangles)
        {
            xRanges.emplace_back(rectangle[0], rectangle[2]);
            yRanges.emplace_back(rectangle[1], rectangle[3]);
        }
        auto comp = [](TRange const &l, TRange const &r) { return (l.first < r.first) || ((l.first == r.first) && (l.second < r.second)); };
        std::ranges::sort(xRanges, comp);
        std::ranges::sort(yRanges, comp);
        return canSeparate(xRanges) || canSeparate(yRanges);
    }

private:
    typedef std::pair<int, int> TRange;

    [[nodiscard]] bool canSeparate(std::vector<TRange> const &ranges) const
    {
        int partsCount = 0;
        int partEnd = ranges.front().first;
        for (TRange const &range : ranges)
        {
            if (partEnd <= range.first)
                ++partsCount;
            partEnd = std::max(partEnd, range.second);
            if (partsCount == 3)
                return true;
        }
        return false;
    }
};

}

namespace CheckIfGridCanBeCutIntoSectionsTask
{

TEST(CheckIfGridCanBeCutIntoSectionsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkValidCuts(5, {{1, 0, 5, 2}, {0, 2, 2, 4}, {3, 2, 5, 3}, {0, 4, 4, 5}}));
    ASSERT_EQ(true, solution.checkValidCuts(4, {{0, 0, 1, 1}, {2, 0, 3, 4}, {0, 2, 2, 3}, {3, 0, 4, 3}}));
    ASSERT_EQ(false, solution.checkValidCuts(4, {{0, 2, 2, 4}, {1, 0, 3, 2}, {2, 2, 3, 4}, {3, 0, 4, 2}, {3, 2, 4, 4}}));
}

}