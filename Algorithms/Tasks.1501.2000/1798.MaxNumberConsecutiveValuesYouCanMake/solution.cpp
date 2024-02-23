#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int getMaximumConsecutive(std::vector<int> const &coins) const
    {
        std::vector<int> sortedCoins(coins);
        std::ranges::sort(sortedCoins);
        int consecutiveCount = 1;
        for (const int coin : sortedCoins)
        {
            if (consecutiveCount < coin)
                break;
            consecutiveCount += coin;
        }
        return consecutiveCount;
    }
};

}

namespace MaxNumberConsecutiveValuesYouCanMakeTask
{

TEST(MaxNumberConsecutiveValuesYouCanMakeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.getMaximumConsecutive({1, 3}));
    ASSERT_EQ(8, solution.getMaximumConsecutive({1, 1, 1, 4}));
    ASSERT_EQ(20, solution.getMaximumConsecutive({1, 4, 10, 3, 1}));
}

}