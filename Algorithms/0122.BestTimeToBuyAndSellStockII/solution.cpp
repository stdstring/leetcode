#include <climits>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxProfit(std::vector<int> const &prices) const
    {
        int profit = 0;
        int bestBuy = INT_MAX;
        for (size_t index = 0; index < prices.size(); ++index)
        {
            if (prices[index] == bestBuy)
                continue;
            if (prices[index] < bestBuy)
                bestBuy = prices[index];
            else if ((index == prices.size() - 1) || (prices[index] > prices[index + 1]))
            {
                profit += (prices[index] - bestBuy);
                bestBuy = INT_MAX;
            }
        }
        return profit;
    }
};

}

namespace BestTimeToBuyAndSellStockIITask
{

TEST(BestTimeToBuyAndSellStockIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(7, solution.maxProfit({7, 1, 5, 3, 6, 4}));
    ASSERT_EQ(4, solution.maxProfit({1, 2, 3, 4, 5}));
    ASSERT_EQ(0, solution.maxProfit({7, 6, 4, 3, 1}));
}

}