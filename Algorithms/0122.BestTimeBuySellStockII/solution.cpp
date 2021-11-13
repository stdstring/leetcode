#include <climits>
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
        for (size_t index = 1; index < prices.size(); ++index)
        {
            buy = std::max(buy, sell - prices[index]);
            sell = std::max(sell, buy + prices[index]);
        }
        return sell;
    }
};

}

namespace BestTimeBuySellStockIITask
{

TEST(BestTimeBuySellStockIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(7, solution.maxProfit({7, 1, 5, 3, 6, 4}));
    ASSERT_EQ(4, solution.maxProfit({1, 2, 3, 4, 5}));
    ASSERT_EQ(0, solution.maxProfit({7, 6, 4, 3, 1}));
}

}