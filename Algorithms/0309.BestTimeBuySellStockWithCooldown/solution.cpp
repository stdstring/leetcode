#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxProfit(std::vector<int> const &prices) const
    {
        int buy = -prices[0];
        int sell = 0;
        int cooldown = 0;
        for (size_t index = 1; index < prices.size(); ++index)
        {
            int beforeSell = sell;
            buy = std::max(buy, cooldown - prices[index]);
            sell = std::max(sell, buy + prices[index]);
            cooldown = std::max(cooldown, beforeSell);
        }
        return std::max(sell, cooldown);
    }
};

}

namespace BestTimeBuySellStockWithCooldownTask
{

TEST(BestTimeBuySellStockWithCooldownTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.maxProfit({1, 2, 3, 0, 2}));
    ASSERT_EQ(0, solution.maxProfit({1}));
}

}