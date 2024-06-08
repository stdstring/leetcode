#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countDays(int days, std::vector<std::vector<int>> const &meetings) const
    {
        auto comp = [](std::vector<int> const &l, std::vector<int> const &r) { return (l[0] < r[0]) || ((l[0] == r[0]) && (l[1] < r[1])); };
        std::vector<std::vector<int>> sortedMeetings(meetings);
        std::ranges::sort(sortedMeetings, comp);
        int meetingsDays = 0;
        int currentDay = 0;
        for (std::vector<int> const &meeting : sortedMeetings)
        {
            if (meeting[1] < currentDay)
                continue;
            meetingsDays += (meeting[1] - std::max(meeting[0], currentDay) + ((meeting[0] > currentDay) ? 1 : 0));
            currentDay = meeting[1];
        }
        return days - meetingsDays;
    }
};

}

namespace CountDaysWithoutMeetingsTask
{

TEST(CountDaysWithoutMeetingsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countDays(10, {{5, 7}, {1, 3}, {9, 10}}));
    ASSERT_EQ(1, solution.countDays(5, {{2, 4}, {1, 3}}));
    ASSERT_EQ(0, solution.countDays(6, {{1, 6}}));
}

}