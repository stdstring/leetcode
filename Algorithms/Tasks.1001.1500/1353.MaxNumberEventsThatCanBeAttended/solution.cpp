#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxEvents(std::vector<std::vector<int>> const &events) const
    {
        std::vector<size_t> indexes(events.size(), 0);
        std::iota(indexes.begin(), indexes.end(), 0);
        auto sortComp = [&events](size_t l, size_t r)
        {
            return (events[l][0] < events[r][0]) || ((events[l][0] == events[r][0]) && (events[l][1] < events[r][1]));
        };
        std::ranges::sort(indexes, sortComp);
        size_t attendedEvents = 0;
        int minDay = events[indexes.front()][0];
        int maxDay = events[std::ranges::max(indexes, [&events](size_t l, size_t r) { return events[l][1] < events[r][1]; })][1];
        auto priorityQueueCmp = [&events, &indexes](size_t l, size_t r) { return events[indexes[l]][1] > events[indexes[r]][1]; };
        std::priority_queue<size_t, std::vector<size_t>, decltype(priorityQueueCmp)> eventsQueue(priorityQueueCmp);
        size_t eventIndex = 0;
        for (int day = minDay; day <= maxDay; ++day)
        {
            while (!eventsQueue.empty() && (events[indexes[eventsQueue.top()]][1] < day))
                eventsQueue.pop();
            for (; (eventIndex < indexes.size()) && (events[indexes[eventIndex]][0] == day); ++eventIndex)
                eventsQueue.emplace(eventIndex);
            if (!eventsQueue.empty())
            {
                ++attendedEvents;
                eventsQueue.pop();
            }
        }
        return static_cast<int>(attendedEvents);
    }
};

}

namespace MaxNumberEventsThatCanBeAttendedTask
{

TEST(MaxNumberEventsThatCanBeAttendedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxEvents({{1, 2}, {2, 3}, {3, 4}}));
    ASSERT_EQ(4, solution.maxEvents({{1, 2}, {2, 3}, {3, 4}, {1, 2}}));
}

TEST(MaxNumberEventsThatCanBeAttendedTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxEvents({{1, 2}, {1, 3}, {1, 4}}));
}

}