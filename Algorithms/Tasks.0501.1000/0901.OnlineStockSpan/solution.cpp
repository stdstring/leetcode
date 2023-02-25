#include <stack>

#include "gtest/gtest.h"

namespace
{

class StockSpanner
{
public:
    StockSpanner() = default;

    int next(int price)
    {
        size_t spanValue = 1;
        while (!_stockStack.empty() && (_stockStack.top().first <= price))
        {
            spanValue += _stockStack.top().second;
            _stockStack.pop();
        }
        _stockStack.emplace(price, spanValue);
        return static_cast<int>(spanValue);
    }

private:
    std::stack<std::pair<int, size_t>> _stockStack;
};

}

namespace OnlineStockSpanTask
{

TEST(OnlineStockSpanTaskTests, Examples)
{
    StockSpanner stockSpanner;
    ASSERT_EQ(1, stockSpanner.next(100));
    ASSERT_EQ(1, stockSpanner.next(80));
    ASSERT_EQ(1, stockSpanner.next(60));
    ASSERT_EQ(2, stockSpanner.next(70));
    ASSERT_EQ(1, stockSpanner.next(60));
    ASSERT_EQ(4, stockSpanner.next(75));
    ASSERT_EQ(6, stockSpanner.next(85));
}

}