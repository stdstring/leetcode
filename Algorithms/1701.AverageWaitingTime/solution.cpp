#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double averageWaitingTime(std::vector<std::vector<int>> const &customers) const
    {
        long long waitTime = 0;
        long long freeTime = 0;
        for (std::vector<int> const &customer : customers)
        {
            if (customer[0] >= freeTime)
                freeTime = customer[0];
            else
                waitTime += (freeTime - customer[0]);
            waitTime += customer[1];
            freeTime += customer[1];
        }
        return static_cast<double>(waitTime) / static_cast<double>(customers.size());
    }
};

}

namespace AverageWaitingTimeTask
{

TEST(AverageWaitingTimeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_DOUBLE_EQ(5.0, solution.averageWaitingTime({{1, 2}, {2, 5}, {4, 3}}));
    ASSERT_DOUBLE_EQ(3.25, solution.averageWaitingTime({{5, 2}, {5, 4}, {10, 3}, {20, 1}}));
}

}