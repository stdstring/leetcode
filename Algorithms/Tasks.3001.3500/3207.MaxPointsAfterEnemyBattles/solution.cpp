#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maximumPoints(std::vector<int> const &enemyEnergies, int currentEnergy) const
    {
        const int minValue = *std::ranges::min_element(enemyEnergies);
        if (minValue > currentEnergy)
            return 0;
        const long long totalSum = std::accumulate(enemyEnergies.cbegin(), enemyEnergies.cend(), 0LL);
        const long long maxEnergy = 0LL + (currentEnergy - minValue) + (totalSum - minValue);
        return 1LL + maxEnergy / minValue;
    }
};

}

namespace MaxPointsAfterEnemyBattlesTask
{

TEST(MaxPointsAfterEnemyBattlesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumPoints({3, 2, 2}, 2));
    ASSERT_EQ(5, solution.maximumPoints({2}, 10));
}

}