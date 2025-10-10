#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumEnergy(std::vector<int> const &energy, int k) const
    {
        const size_t step = k;
        std::vector<int> dp(energy.size(), 0);
        int maxValue = INT_MIN;
        for (size_t index = 0; index < energy.size(); ++index)
        {
            const int maxEnding = (index < step) ? energy[index] : (energy[index] + std::max(0, dp[index - step]));
            dp[index] = maxEnding;
            if ((index + step) >= energy.size())
                maxValue = std::max(maxValue, maxEnding);
        }
        return maxValue;
    }
};

}

namespace TakingMaxEnergyFromMysticDungeonTask
{

TEST(TakingMaxEnergyFromMysticDungeonTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumEnergy({5, 2, -10, -5, 1}, 3));
    ASSERT_EQ(-1, solution.maximumEnergy({-2, -3, -1}, 2));
}

}