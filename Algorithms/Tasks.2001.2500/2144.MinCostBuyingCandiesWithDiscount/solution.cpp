#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumCost(std::vector<int> const &cost) const
    {
        std::vector<int> sortedCost(cost);
        std::ranges::sort(sortedCost, std::greater<int>());
        int result = 0;
        for (size_t index = 0; index < sortedCost.size(); ++index)
        {
            if ((index % 3) != 2)
                result += sortedCost[index];
        }
        return result;
    }
};

}

namespace MinCostBuyingCandiesWithDiscountTask
{

TEST(MinCostBuyingCandiesWithDiscountTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minimumCost({1, 2, 3}));
    ASSERT_EQ(23, solution.minimumCost({6, 5, 7, 9, 2, 2}));
    ASSERT_EQ(10, solution.minimumCost({5, 5}));
}

}