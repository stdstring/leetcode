#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int removeCoveredIntervals(std::vector<std::vector<int>> const &intervals) const
    {
        std::vector<std::vector<int>> sortedIntervals(intervals);
        std::sort(sortedIntervals.begin(), sortedIntervals.end(), [](std::vector<int> const &l, std::vector<int> const &r){ return (l[0] < r[0]) || ((l[0] == r[0]) && (l[1] > r[1])); });
        size_t noncoveredIntervalsCount = 1;
        size_t currentIntervalIndex = 0;
        for (size_t index = 1; index < sortedIntervals.size(); ++index)
        {
            if (sortedIntervals[currentIntervalIndex][1] < sortedIntervals[index][1])
            {
                currentIntervalIndex = index;
                ++noncoveredIntervalsCount;
            }
        }
        return static_cast<int>(noncoveredIntervalsCount);
    }
};

}

namespace RemoveCoveredIntervalsTask
{

TEST(RemoveCoveredIntervalsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.removeCoveredIntervals({{1, 4}, {3, 6}, {2, 8}}));
    ASSERT_EQ(1, solution.removeCoveredIntervals({{1, 4}, {2, 3}}));
}

}