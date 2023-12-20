#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int buyChoco(std::vector<int> const &prices, int money) const
    {
        int cost1 = std::min(prices[0], prices[1]);
        int cost2 = std::max(prices[0], prices[1]);
        for (size_t index = 2; index < prices.size(); ++index)
        {
            if (prices[index] <= cost1)
            {
                cost2 = cost1;
                cost1 = prices[index];
            }
            else if (prices[index] < cost2)
                cost2 = prices[index];
        }
        const int totalCost = cost1 + cost2;
        return money - (totalCost <= money ? totalCost : 0);
    }
};

}

namespace BuyTwoChocolatesTask
{

TEST(BuyTwoChocolatesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.buyChoco({1, 2, 2}, 3));
    ASSERT_EQ(3, solution.buyChoco({3, 2, 3}, 3));
}

}