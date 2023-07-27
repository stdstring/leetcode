#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxRunTime(int n, std::vector<int> const &batteries) const
    {
        std::vector<int> sortedBatteries(batteries);
        std::ranges::sort(sortedBatteries, std::greater<>());
        long long totalCapacity = std::accumulate(sortedBatteries.cbegin(), sortedBatteries.cend(), 0LL);
        size_t current = 0;
        while (sortedBatteries[current] > (totalCapacity / n))
        {
            totalCapacity -= sortedBatteries[current];
            --n;
            ++current;
        }
        return totalCapacity / n;
    }
};

}

namespace MaxRunningTimeOfNComputersTask
{

TEST(MaxRunningTimeOfNComputersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxRunTime(2, {3, 3, 3}));
    ASSERT_EQ(2, solution.maxRunTime(2, {1, 1, 1, 1}));
}

}