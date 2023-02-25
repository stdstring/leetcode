#include <cstdint>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countOrders(int n) const
    {
        constexpr int modValue = 1000000007;
        int64_t orders = 1;
        for (int64_t prevCount = 1; prevCount < n; ++prevCount)
        {
            // binomial coefficient C(k = 2, n = 2 * prevCount + 1):
            const int64_t binomialCoeff = prevCount * (2 * prevCount + 1);
            orders = orders * ((2 * prevCount + 1) + binomialCoeff) % modValue;
        }
        return static_cast<int>(orders);
    }
};

}

namespace CountAllValidPickupAndDeliveryOptionsTask
{

TEST(CountAllValidPickupAndDeliveryOptionsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.countOrders(1));
    ASSERT_EQ(6, solution.countOrders(2));
    ASSERT_EQ(90, solution.countOrders(3));
}

}