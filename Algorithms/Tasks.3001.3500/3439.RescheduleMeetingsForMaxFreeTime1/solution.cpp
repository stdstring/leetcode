#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxFreeTime(int eventTime, int k, std::vector<int> const &startTime, std::vector<int> const &endTime) const
    {
        // TODO (std_string) : think about solution without intervals
        std::vector<int> intervals;
        intervals.emplace_back(startTime[0]);
        for (size_t index = 1; index < startTime.size(); ++index)
            intervals.emplace_back(startTime[index] - endTime[index - 1]);
        intervals.emplace_back(eventTime - endTime.back());
        int bestFreeTime = 0;
        // init sliding window
        for (size_t index = 0; index < (k + 1); ++index)
            bestFreeTime += intervals[index];
        // move sliding window
        int currentFreeTime = bestFreeTime;
        for (size_t index = (k + 1); index < intervals.size(); ++index)
        {
            currentFreeTime += intervals[index];
            currentFreeTime -= intervals[index - (k + 1)];
            bestFreeTime = std::max(bestFreeTime, currentFreeTime);
        }
        return bestFreeTime;
    }
};

}

namespace RescheduleMeetingsForMaxFreeTime1Task
{

TEST(RescheduleMeetingsForMaxFreeTime1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxFreeTime(5, 1, {1, 3}, {2, 5}));
    ASSERT_EQ(6, solution.maxFreeTime(10, 1, {0, 2, 9}, {1, 4, 10}));
    ASSERT_EQ(0, solution.maxFreeTime(5, 2, {0, 1, 2, 3, 4}, {1, 2, 3, 4, 5}));
}

TEST(RescheduleMeetingsForMaxFreeTime1TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxFreeTime(5, 2, {1, 3}, {2, 5}));
}

TEST(RescheduleMeetingsForMaxFreeTime1TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.maxFreeTime(21, 1, {7, 10, 16}, {10, 14, 18}));
}

}