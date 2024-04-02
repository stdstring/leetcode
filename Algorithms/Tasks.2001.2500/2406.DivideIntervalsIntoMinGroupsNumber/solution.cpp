#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minGroups(std::vector<std::vector<int>> const &intervals) const
    {
        std::vector<std::pair<int, int>> intervalChanges;
        intervalChanges.reserve(2 * intervals.size());
        for (std::vector<int> const &interval : intervals)
        {
            intervalChanges.emplace_back(std::pair<int, int>(interval[0], 1));
            intervalChanges.emplace_back(std::pair<int, int>(interval[1], -1));
        }
        auto comp = [](std::pair<int, int> const &l, std::pair<int, int> const &r)
        {
            return (l.first < r.first) || ((l.first == r.first) && (l.second > r.second));
        };
        std::ranges::sort(intervalChanges, comp);
        int maxIntersect = 0;
        int currentIntersect = 0;
        for (std::pair<int, int> const &change : intervalChanges)
        {
            currentIntersect += change.second;
            maxIntersect = std::max(maxIntersect, currentIntersect);
        }
        return maxIntersect;
    }
};

}

namespace DivideIntervalsIntoMinGroupsNumberTask
{

TEST(DivideIntervalsIntoMinGroupsNumberTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minGroups({{5, 10}, {6, 8}, {1, 5}, {2, 3}, {1, 10}}));
    ASSERT_EQ(1, solution.minGroups({{1, 3}, {5, 6}, {8, 10}, {11, 13}}));
}

TEST(DivideIntervalsIntoMinGroupsNumberTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minGroups({{1, 1}}));
}

TEST(DivideIntervalsIntoMinGroupsNumberTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minGroups({{1, 1}, {1, 1}}));
}

}