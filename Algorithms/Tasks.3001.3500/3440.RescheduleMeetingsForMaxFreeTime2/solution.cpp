#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxFreeTime(int eventTime, std::vector<int> const &startTime, std::vector<int> const &endTime) const
    {
        std::vector<int> intervals;
        intervals.emplace_back(startTime.front());
        std::vector<size_t> best3Intervals;
        best3Intervals.emplace_back(0);
        for (size_t index = 1; index <= startTime.size(); ++index)
        {
            size_t intervalIndex = intervals.size();
            int interval = ((index == startTime.size()) ? eventTime : startTime[index]) - endTime[index - 1];
            intervals.emplace_back(interval);
            add2Best3Intervals(intervals, intervalIndex, best3Intervals);
        }
        int bestFreeTime = 0;
        for (size_t index = 0; index < startTime.size(); ++index)
        {
            const int duration = endTime[index] - startTime[index];
            const int freeTime = intervals[index] + intervals[index + 1] +
                                 (canMove(intervals, best3Intervals, duration, index, index + 1) ? duration : 0);
            bestFreeTime = std::max(bestFreeTime, freeTime);
        }
        return bestFreeTime;
    }

private:
    void add2Best3Intervals(std::vector<int> const &intervals, size_t current, std::vector<size_t> &best3Intervals) const
    {
        best3Intervals.emplace_back(current);
        for (size_t rIndex = 1; rIndex < best3Intervals.size(); ++rIndex)
        {
            size_t index = best3Intervals.size() - 1 - rIndex;
            if (intervals[best3Intervals[index]] >= intervals[best3Intervals[index + 1]])
                break;
            std::swap(best3Intervals[index], best3Intervals[index + 1]);
        }
        if (best3Intervals.size() > 3)
            best3Intervals.pop_back();
    }

    [[nodiscard]] bool canMove(std::vector<int> const &intervals, std::vector<size_t> const &best3Intervals, int duration, size_t left, size_t right) const
    {
        for (size_t current : best3Intervals)
        {
            if ((current == left) || (current == right))
                continue;
            return intervals[current] >= duration;
        }
        return false;
    }
};

}

namespace RescheduleMeetingsForMaxFreeTime2Task
{

TEST(RescheduleMeetingsForMaxFreeTime2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxFreeTime(5, {1, 3}, {2, 5}));
    ASSERT_EQ(7, solution.maxFreeTime(10, {0, 7, 9}, {1, 8, 10}));
    ASSERT_EQ(6, solution.maxFreeTime(10, {0, 3, 7, 9}, {1, 4, 8, 10}));
    ASSERT_EQ(0, solution.maxFreeTime(5, {0, 1, 2, 3, 4}, {1, 2, 3, 4, 5}));
}

}