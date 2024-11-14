#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimizedMaximum(int n, std::vector<int> const &quantities) const
    {
        const int maxQuantity = std::ranges::max(quantities);
        int left = 1;
        int right = maxQuantity;
        while (left < right)
        {
            int middle = (left + right) / 2;
            if (canDistribute(n, quantities, middle))
                right = middle;
            else
                left = middle + 1;
        }
        return left;
    }

private:
    [[nodiscard]] bool canDistribute(int n, std::vector<int> const &quantities, int maxPortion) const
    {
        int retailCount = 0;
        for (int quantity : quantities)
            retailCount += (quantity / maxPortion) + ((quantity % maxPortion) == 0 ? 0 : 1);
        return retailCount <= n;
    }
};

}

namespace MinMaxProductsDistributedAnyStoreTask
{

TEST(MinMaxProductsDistributedAnyStoreTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimizedMaximum(6, {11, 6}));
    ASSERT_EQ(5, solution.minimizedMaximum(7, {15, 10, 10}));
    ASSERT_EQ(100000, solution.minimizedMaximum(1, {100000}));
}

}