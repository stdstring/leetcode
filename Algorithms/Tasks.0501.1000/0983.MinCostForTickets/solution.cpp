#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int mincostTickets(std::vector<int> const &days, std::vector<int> const &costs) const
    {
        const std::vector<std::pair<int, int>> tickets({{1, costs[0]}, {7, costs[1]}, {30, costs[2]}});
        std::vector<int> dp(days.size(), INT_MAX);
        for (size_t index = 0; index < dp.size(); ++index)
        {
            for (std::pair<int, int> const &ticket : tickets)
            {
                const size_t endRangeIndex = calcEndRangeIndex(days, index, ticket.first);
                dp[endRangeIndex] = std::min(dp[endRangeIndex], (index == 0 ? 0 : dp[index - 1]) + ticket.second);
            }
        }
        return dp.back();
    }

private:
    [[nodiscard]] size_t calcEndRangeIndex(std::vector<int> const &days, size_t startRangeIndex, int daysCount) const
    {
        if (daysCount == 1)
            return startRangeIndex;
        size_t currentIndex = startRangeIndex;
        while ((currentIndex < days.size()) && (days[currentIndex] - days[startRangeIndex] + 1 <= daysCount))
            ++currentIndex;
        return currentIndex - 1;
    }
};

}

namespace MinCostForTicketsTask
{

TEST(MinCostForTicketsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(11, solution.mincostTickets({1, 4, 6, 7, 8, 20}, {2, 7, 15}));
    ASSERT_EQ(17, solution.mincostTickets({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31}, {2, 7, 15}));
}

}