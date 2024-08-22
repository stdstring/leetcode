#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxEnergyBoost(std::vector<int> const &energyDrinkA, std::vector<int> const &energyDrinkB) const
    {
        size_t n = energyDrinkA.size();
        std::vector<std::pair<long long, long long>> dp(n);
        dp[0].first = energyDrinkA[0];
        dp[0].second = energyDrinkB[0];
        for (size_t index = 0; index < (n - 1); ++index)
        {
            dp[index + 1].first = std::max(dp[index + 1].first, dp[index].first + energyDrinkA[index + 1]);
            dp[index + 1].second = std::max(dp[index + 1].second, dp[index].second + energyDrinkB[index + 1]);
            if ((index + 2) < n)
            {
                dp[index + 2].first = dp[index].second + energyDrinkA[index + 2];
                dp[index + 2].second = dp[index].first + energyDrinkB[index + 2];
            }
        }
        return std::max(dp.back().first, dp.back().second);
    }
};

}

namespace MaxEnergyBoostFromTwoDrinksTask
{

TEST(MaxEnergyBoostFromTwoDrinksTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.maxEnergyBoost({1, 3, 1}, {3, 1, 1}));
    ASSERT_EQ(7, solution.maxEnergyBoost({4, 1, 1}, {1, 1, 3}));
}

}