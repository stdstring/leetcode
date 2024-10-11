#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int smallestChair(std::vector<std::vector<int>> const &times, int targetFriend) const
    {
        const int n = static_cast<int>(times.size());
        std::vector<int> usedChairs(n, -1);
        std::vector<Event> events;
        events.reserve(2LL * n);
        for (int friendNumber = 0; friendNumber < n; ++friendNumber)
        {
            events.emplace_back(times[friendNumber][0], friendNumber, true);
            events.emplace_back(times[friendNumber][1], friendNumber, false);
        }
        std::ranges::sort(events, [](Event const &l, Event const &r){ return (l.Time < r.Time) || ((l.Time == r.Time) && (l.Start < r.Start)); });
        std::set<int> freeChairs;
        for (int chair = 0; chair < n; ++chair)
            freeChairs.insert(chair);
        for (Event const &event : events)
        {
            if (event.Start)
            {
                const int chair = *freeChairs.cbegin();
                freeChairs.erase(freeChairs.cbegin());
                usedChairs[event.FriendNumber] = chair;
                if (event.FriendNumber == targetFriend)
                    return chair;
            }
            else
            {
                const int chair = usedChairs[event.FriendNumber];
                freeChairs.insert(chair);
                usedChairs[event.FriendNumber] = -1;
            }
        }
        return -1;
    }

private:
    struct Event
    {
        Event(int time, int friendNumber, bool start) : Time(time), FriendNumber(friendNumber), Start(start)
        {
        }

        int Time;
        int FriendNumber;
        bool Start;
    };
};

}

namespace NumberOfSmallestUnoccupiedChairTask
{

TEST(NumberOfSmallestUnoccupiedChairTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.smallestChair({{1, 4}, {2, 3}, {4, 6}}, 1));
    ASSERT_EQ(2, solution.smallestChair({{3, 10}, {1, 5}, {2, 6}}, 0));
}

TEST(NumberOfSmallestUnoccupiedChairTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(45, solution.smallestChair({{3, 100000}, {37, 100000}, {34, 100000}, {16, 100000}, {28, 100000},
                                          {19, 100000}, {14, 100000}, {29, 100000}, {5, 100000}, {9, 100000},
                                          {25, 100000}, {18, 100000}, {31, 100000}, {17, 100000}, {12, 100000},
                                          {36, 100000}, {30, 100000}, {13, 100000}, {27, 100000}, {10, 100000},
                                          {21, 100000}, {38, 100000}, {11, 100000}, {46, 100000}, {2, 100000},
                                          {33, 100000}, {20, 100000}, {8, 100000}, {35, 100000}, {43, 100000},
                                          {23, 100000}, {22, 100000}, {15, 100000}, {44, 100000}, {45, 100000},
                                          {7, 100000}, {24, 100000}, {42, 100000}, {6, 100000}, {1, 100000},
                                          {26, 100000}, {39, 100000}, {32, 100000}, {40, 100000}, {41, 100000}, {4, 100000}}, 23));
    ASSERT_EQ(0, solution.smallestChair({{18, 19}, {10, 11}, {21, 22}, {5, 6}, {2, 3}, {6, 7}, {43, 44}, {48, 49}, {53, 54}, {12, 13},
                                         {20, 21}, {34, 35}, {17, 18}, {1, 2}, {35, 36}, {16, 17}, {9, 10}, {14, 15}, {25, 26}, {37, 38},
                                         {30, 31}, {50, 51}, {22, 23}, {3, 4}, {27, 28}, {29, 30}, {33, 34}, {39, 40}, {49, 50}, {15, 16},
                                         {4, 5}, {46, 47}, {51, 52}, {32, 33}, {11, 12}, {28, 29}, {47, 48}, {36, 37}, {40, 41}, {42, 43},
                                         {52, 53}, {41, 42}, {31, 32}, {23, 24}, {8, 9}, {19, 20}, {24, 25}, {26, 27}, {45, 46}, {44, 45},
                                         {7, 8}, {13, 14}, {38, 39}}, 8));
}

}