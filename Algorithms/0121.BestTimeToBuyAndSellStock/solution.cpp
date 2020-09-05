#include <algorithm>
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
        size_t buyIndex = 0;
        for (size_t index = 1; index < prices.size(); ++index)
        {
            if (prices[buyIndex] > prices[index])
                buyIndex = index;
            else
                profit = std::max(profit, prices[index] - prices[buyIndex]);
        }
        return profit;
    }
};

}

namespace BestTimeToBuyAndSellStockTask
{

TEST(BestTimeToBuyAndSellStockTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.maxProfit({7, 1, 5, 3, 6, 4}));
    ASSERT_EQ(0, solution.maxProfit({7, 6, 4, 3, 1}));
}

}