#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool carPooling(std::vector<std::vector<int>> const &trips, int capacity) const
    {
        std::vector<std::pair<int, int>> events;
        events.reserve(2 * trips.size());
        for (std::vector<int> const &trip : trips)
        {
            events.emplace_back(trip[0], trip[1]);
            events.emplace_back(-trip[0], trip[2]);
        }
        std::sort(events.begin(), events.end(), [](std::pair<int, int> const &l, std::pair<int, int> const &r){ return l.second < r.second || ((l.second == r.second) && (l.first < r.first)); });
        int occupied = 0;
        for (std::pair<int, int> const &event : events)
        {
            occupied += event.first;
            if (occupied > capacity)
                return false;
        }
        return true;
    }
};

}

namespace CarPoolingTask
{

TEST(CarPoolingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.carPooling({{2, 1, 5}, {3, 3, 7}}, 4));
    ASSERT_EQ(true, solution.carPooling({{2, 1, 5}, {3, 3, 7}}, 5));
}

TEST(CarPoolingTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.carPooling({{4, 5, 6}, {6, 4, 7}, {4, 3, 5}, {2, 3, 5}}, 13));
}

}