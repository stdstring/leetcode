#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>> const &intervals) const
    {
        if (intervals.empty())
            return 0;
        std::vector<std::vector<int>> sortedIntervals(intervals);
        std::sort(sortedIntervals.begin(), sortedIntervals.end(), [](std::vector<int> const &left, std::vector<int> const &right){ return left[1] < right[1]; });
        size_t lastIndex = 0;
        size_t nonOverlappingCount = 1;
        for (size_t index = 1; index < sortedIntervals.size(); ++index)
        {
            if (sortedIntervals[index][0] >= sortedIntervals[lastIndex][1])
            {
                lastIndex = index;
                ++nonOverlappingCount;
            }
        }
        return static_cast<int>(intervals.size() - nonOverlappingCount);
    }
};

}

namespace NonOverlappingIntervalsTask
{

TEST(NonOverlappingIntervalsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.eraseOverlapIntervals({{1, 2}, {2, 3}, {3, 4}, {1, 3}}));
    ASSERT_EQ(2, solution.eraseOverlapIntervals({{1, 2}, {1, 2}, {1, 2}}));
    ASSERT_EQ(0, solution.eraseOverlapIntervals({{1, 2}, {2, 3}}));
}

}