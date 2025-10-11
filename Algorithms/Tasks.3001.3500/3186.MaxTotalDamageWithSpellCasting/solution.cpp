#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maximumTotalDamage(std::vector<int> const &power) const
    {
        // prepare
        std::map<int, int> powerMap;
        for (int value : power)
            ++powerMap[value];
        typedef std::pair<int, int> TPowerData;
        std::vector<TPowerData> powerData(powerMap.cbegin(), powerMap.cend());
        // dp
        std::vector<long long> dp(powerData.size(), 0);
        long long maxDamage = 0;
        for (size_t index = 0; index < dp.size(); ++index)
        {
            long long prevDp = dp[index];
            auto [value, count] = powerData[index];
            dp[index] = std::max(dp[index], prevDp + 1LL * value * count);
            for (size_t next = index + 1; next < dp.size(); ++next)
            {
                auto [nextValue, _] = powerData[next];
                if ((nextValue - value) <= 2)
                    dp[next] = std::max(dp[next], prevDp);
                else
                {
                    dp[next] = std::max(dp[next], dp[index]);
                    break;
                }
            }
            maxDamage = std::max(std::max(maxDamage, prevDp), dp[index]);
        }
        return maxDamage;
    }
};

}

namespace MaxTotalDamageWithSpellCastingTask
{

TEST(MaxTotalDamageWithSpellCastingTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.maximumTotalDamage({1, 1, 3, 4}));
    ASSERT_EQ(13, solution.maximumTotalDamage({7, 1, 6, 6}));
}

}