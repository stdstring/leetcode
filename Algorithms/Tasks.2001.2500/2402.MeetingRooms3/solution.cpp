#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int mostBooked(int n, std::vector<std::vector<int>> const &meetings) const
    {
        std::vector<std::vector<int>> sortedMeetings(meetings);
        std::ranges::sort(sortedMeetings, [](std::vector<int> const &l, std::vector<int> const &r) { return l[0] < r[0]; });
        std::vector<int> roomUsage(n, 0);
        std::priority_queue<int, std::vector<int>, std::greater<>> freeRoomsQueue;
        for (int room = 0; room < n; ++room)
            freeRoomsQueue.emplace(room);
        // meetingQueue - finishTime, room
        auto meetingComp = [](std::pair<long long, int> const &l, std::pair<long long, int> const &r)
        {
            return (l.first > r.first) || ((l.first == r.first) && (l.second > r.second));
        };
        std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, decltype(meetingComp)> meetingQueue(meetingComp);
        for (auto const &currentMeeting : sortedMeetings)
        {
            while (!meetingQueue.empty() && (meetingQueue.top().first <= currentMeeting[0]))
            {
                freeRoomsQueue.emplace(meetingQueue.top().second);
                meetingQueue.pop();
            }
            if (freeRoomsQueue.empty())
            {
                auto const [startTime, room] = meetingQueue.top();
                meetingQueue.pop();
                ++roomUsage[room];
                meetingQueue.emplace(startTime + currentMeeting[1] - currentMeeting[0], room);
            }
            else
            {
                const int room = freeRoomsQueue.top();
                freeRoomsQueue.pop();
                ++roomUsage[room];
                meetingQueue.emplace(currentMeeting[1], room);
            }
        }
        int mostBookedRoom = 0;
        for (int room = 0; room < n; ++room)
        {
            if (roomUsage[mostBookedRoom] < roomUsage[room])
                mostBookedRoom = room;
        }
        return mostBookedRoom;
    }
};

}

namespace MeetingRooms3Task
{

TEST(MeetingRooms3TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.mostBooked(2, {{0, 10}, {1, 5}, {2, 7}, {3, 4}}));
    ASSERT_EQ(1, solution.mostBooked(3, {{1, 20}, {2, 10}, {3, 5}, {4, 9}, {6, 8}}));
}

}