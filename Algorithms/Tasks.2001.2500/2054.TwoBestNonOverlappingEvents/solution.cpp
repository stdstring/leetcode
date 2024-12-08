#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxTwoEvents(std::vector<std::vector<int>> const &events) const
    {
        std::vector<size_t> startSortedIndices(events.size(), 0);
        std::iota(startSortedIndices.begin(), startSortedIndices.end(), 0);
        std::ranges::sort(startSortedIndices, [&events](size_t l, size_t r) { return (events[l][0] < events[r][0]); });
        std::vector<size_t> endSortedIndices(events.size(), 0);
        std::iota(endSortedIndices.begin(), endSortedIndices.end(), 0);
        std::ranges::sort(endSortedIndices, [&events](size_t l, size_t r) { return (events[l][1] < events[r][1]); });
        int bestEventsValue = 0;
        int bestEndValue = 0;
        for (size_t startIndex = 0, endIndex = 0; startIndex < startSortedIndices.size(); ++startIndex)
        {
            for (; events[endSortedIndices[endIndex + 1]][1] < events[startSortedIndices[startIndex]][0]; ++endIndex)
                bestEndValue = std::max(bestEndValue, events[endSortedIndices[endIndex]][2]);
            if (events[endSortedIndices[endIndex]][1] < events[startSortedIndices[startIndex]][0])
                bestEndValue = std::max(bestEndValue, events[endSortedIndices[endIndex]][2]);
            bestEventsValue = std::max(bestEventsValue, bestEndValue + events[startSortedIndices[startIndex]][2]);
        }
        return bestEventsValue;
    }
};

}

namespace TwoBestNonOverlappingEventsTask
{

TEST(TwoBestNonOverlappingEventsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxTwoEvents({{1, 3, 2}, {4, 5, 2}, {2, 4, 3}}));
    ASSERT_EQ(5, solution.maxTwoEvents({{1, 3, 2}, {4, 5, 2}, {1, 5, 5}}));
    ASSERT_EQ(8, solution.maxTwoEvents({{1, 5, 3}, {1, 5, 1}, {6, 6, 5}}));
}

TEST(TwoBestNonOverlappingEventsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxTwoEvents({ {1, 3, 2}, {2, 4, 3} }));
}

}