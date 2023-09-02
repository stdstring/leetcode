#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Cashier
{
public:
    Cashier(int n, int discount, std::vector<int> const &products, std::vector<int> const &prices) : _n(n), _discount(discount)
    {
        for (size_t index = 0; index < products.size(); ++index)
            _products.emplace(products[index], prices[index]);
    }

    double getBill(std::vector<int> const &product, std::vector<int> const &amount)
    {
        ++_current;
        double total = 0;
        for (size_t index = 0; index < product.size(); ++index)
            total += amount[index] * _products[product[index]];
        if ((_current % _n) == 0)
            total *= ((100.0 - _discount) / 100.0);
        return total;
    }

private:
    int _current = 0;
    const int _n;
    const int _discount;
    std::unordered_map<int, int> _products;
};

}

namespace ApplyDiscountEveryNOrdersTask
{

TEST(ApplyDiscountEveryNOrdersTaskTests, Examples)
{
    Cashier cashier(3, 50, {1, 2, 3, 4, 5, 6, 7}, {100, 200, 300, 400, 300, 200, 100});
    ASSERT_NEAR(500.0, cashier.getBill({1, 2}, {1, 2}), 0.00001);
    ASSERT_NEAR(4000.0, cashier.getBill({3, 7}, {10, 10}), 0.00001);
    ASSERT_NEAR(800.0, cashier.getBill({1, 2, 3, 4, 5, 6, 7}, {1, 1, 1, 1, 1, 1, 1}), 0.00001);
    ASSERT_NEAR(4000.0, cashier.getBill({4}, {10}), 0.00001);
    ASSERT_NEAR(4000.0, cashier.getBill({7, 3}, {10, 10}), 0.00001);
    ASSERT_NEAR(7350.0, cashier.getBill({7, 5, 3, 1, 6, 4, 2}, {10, 10, 10, 9, 9, 9, 7}), 0.00001);
    ASSERT_NEAR(2500.0, cashier.getBill({2, 3, 5}, {5, 3, 2}), 0.00001);
}

}