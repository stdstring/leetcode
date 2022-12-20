#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canVisitAllRooms(std::vector<std::vector<int>> const &rooms) const
    {
        const size_t roomsCount = rooms.size();
        std::vector<bool> visited(roomsCount, false);
        std::queue<int> queue;
        visited[0] = true;
        queue.push(0);
        while (!queue.empty())
        {
            for (int room : rooms[queue.front()])
            {
                if (!visited[room])
                {
                    visited[room] = true;
                    queue.push(room);
                }
            }
            queue.pop();
        }
        return std::all_of(visited.cbegin(), visited.cend(), [](bool value){ return value; });
    }
};

}

namespace KeysAndRoomsTask
{

TEST(KeysAndRoomsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canVisitAllRooms({{1}, {2}, {3}, {}}));
    ASSERT_EQ(false, solution.canVisitAllRooms({{1, 3}, {3, 0, 1}, {2}, {0}}));
}

}