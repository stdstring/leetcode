#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> finalPrices(std::vector<int> const &prices) const
    {
        std::vector<int> result(prices.size(), 0);
        std::stack<int> discounts;
        for (size_t rIndex = 0; rIndex < result.size(); ++rIndex)
        {
            const size_t index = result.size() - 1 - rIndex;
            while (!discounts.empty() && (discounts.top() > prices[index]))
                discounts.pop();
            result[index] = prices[index] - (discounts.empty() ? 0 : discounts.top());
            discounts.push(prices[index]);
        }
        return result;
    }
};

}

namespace FinalPricesWithSpecialDiscountInShopTask
{

TEST(FinalPricesWithSpecialDiscountInShopTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({4, 2, 4, 2, 3}), solution.finalPrices({8, 4, 6, 2, 3}));
    ASSERT_EQ(std::vector<int>({1, 2, 3, 4, 5}), solution.finalPrices({1, 2, 3, 4, 5}));
    ASSERT_EQ(std::vector<int>({9, 0, 1, 6}), solution.finalPrices({10, 1, 1, 6}));
}

}