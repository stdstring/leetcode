#include <vector>

#include "gtest/gtest.h"

namespace
{

class ProductOfNumbers
{
public:
    ProductOfNumbers()
    {
    }

    void add(int num)
    {
        if (num == 0)
            _prefixProducts.clear();
        else
            _prefixProducts.push_back(num * (_prefixProducts.empty() ? 1 : _prefixProducts.back()));
    }

    int getProduct(int k)
    {
        const size_t portionSize = k;
        if (portionSize > _prefixProducts.size())
            return 0;
        if (portionSize == _prefixProducts.size())
            return _prefixProducts.back();
        return _prefixProducts.back() / _prefixProducts[_prefixProducts.size() - 1 - portionSize];
    }

private:
    std::vector<int> _prefixProducts;
};

}

namespace ProductOfLastKNumbersTask
{

TEST(ProductOfLastKNumbersTaskTests, Examples)
{
    ProductOfNumbers productOfNumbers;
    ASSERT_NO_THROW(productOfNumbers.add(3));
    ASSERT_NO_THROW(productOfNumbers.add(0));
    ASSERT_NO_THROW(productOfNumbers.add(2));
    ASSERT_NO_THROW(productOfNumbers.add(5));
    ASSERT_NO_THROW(productOfNumbers.add(4));
    ASSERT_EQ(20, productOfNumbers.getProduct(2));
    ASSERT_EQ(40, productOfNumbers.getProduct(3));
    ASSERT_EQ(0, productOfNumbers.getProduct(4));
    ASSERT_NO_THROW(productOfNumbers.add(8));
    ASSERT_EQ(32, productOfNumbers.getProduct(2));
}

}