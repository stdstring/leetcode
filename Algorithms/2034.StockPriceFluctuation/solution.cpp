#include <map>

#include "gtest/gtest.h"

namespace
{

class StockPrice
{
public:
    StockPrice() = default;

    void update(int timestamp, int price)
    {
        const auto timestampMapIterator = _timestampMap.find(timestamp);
        if (timestampMapIterator == _timestampMap.end())
        {
            _timestampMap.emplace(timestamp, price);
            ++_priceMap[price];
            return;
        }
        const auto priceMapIterator = _priceMap.find(timestampMapIterator->second);
        --priceMapIterator->second;
        if (priceMapIterator->second == 0)
            _priceMap.erase(priceMapIterator);
        timestampMapIterator->second = price;
        ++_priceMap[price];
    }

    [[nodiscard]] int current() const
    {
        return _timestampMap.crbegin()->second;
    }

    [[nodiscard]] int maximum() const
    {
        return _priceMap.crbegin()->first;
    }

    [[nodiscard]] int minimum() const
    {
        return _priceMap.cbegin()->first;
    }

private:
    std::map<int, int> _timestampMap;
    std::map<int, int> _priceMap;
};

}

namespace StockPriceFluctuationTask
{

TEST(StockPriceFluctuationTaskTests, Examples)
{
    StockPrice stockPrice;
    ASSERT_NO_THROW(stockPrice.update(1, 10));
    ASSERT_NO_THROW(stockPrice.update(2, 5));
    ASSERT_EQ(5, stockPrice.current());
    ASSERT_EQ(10, stockPrice.maximum());
    ASSERT_NO_THROW(stockPrice.update(1, 3));
    ASSERT_EQ(5, stockPrice.maximum());
    ASSERT_NO_THROW(stockPrice.update(4, 2));
    ASSERT_EQ(2, stockPrice.minimum());
}

TEST(StockPriceFluctuationTaskTests, CustomExamples)
{
    StockPrice stockPrice;
    ASSERT_NO_THROW(stockPrice.update(1, 10));
    ASSERT_NO_THROW(stockPrice.update(2, 5));
    ASSERT_EQ(5, stockPrice.current());
    ASSERT_EQ(10, stockPrice.maximum());
    ASSERT_NO_THROW(stockPrice.update(1, 3));
    ASSERT_EQ(5, stockPrice.current());
    ASSERT_EQ(5, stockPrice.maximum());
    ASSERT_NO_THROW(stockPrice.update(4, 2));
    ASSERT_EQ(2, stockPrice.minimum());
}

}