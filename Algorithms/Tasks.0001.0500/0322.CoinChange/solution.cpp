#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int coinChange(std::vector<int> const &coins, int amount) const
    {
        if (amount == 0)
            return 0;
        std::vector<size_t> minAmounts(amount + 1, INT_MAX);
        for (int coin : coins)
        {
            if (coin > amount)
                continue;
            minAmounts[coin] = 1;
            for (int number = 1; number <= amount - coin; ++number)
            {
                if (minAmounts[number] != INT_MAX)
                    minAmounts[number + coin] = std::min(minAmounts[number + coin], minAmounts[number] + 1);
            }
        }
        return minAmounts.back() == INT_MAX ? -1 : static_cast<int>(minAmounts.back());
    }
};

}

namespace CoinChangeTask
{

TEST(CoinChangeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.coinChange({1, 2, 5}, 11));
    ASSERT_EQ(-1, solution.coinChange({2}, 3));
    ASSERT_EQ(0, solution.coinChange({1}, 0));
    ASSERT_EQ(1, solution.coinChange({1}, 1));
    ASSERT_EQ(2, solution.coinChange({1}, 2));
}

TEST(CoinChangeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(-1, solution.coinChange({2}, 1));
}


}