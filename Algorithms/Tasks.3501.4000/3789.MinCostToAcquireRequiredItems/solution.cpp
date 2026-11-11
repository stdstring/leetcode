#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) const
    {
        long long result = 1LL * std::min(cost1 + cost2, costBoth) * std::min(need1, need2);
        if (need1 > need2)
            result += 1LL * std::min(cost1, costBoth) * (need1 - need2);
        if (need2 > need1)
            result += 1LL * std::min(cost2, costBoth) * (need2 - need1);
        return result;
    }
};

}

namespace MinCostToAcquireRequiredItemsTask
{

TEST(MinCostToAcquireRequiredItemsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumCost(3, 2, 1, 3, 2));
    ASSERT_EQ(22, solution.minimumCost(5, 4, 15, 2, 3));
    ASSERT_EQ(0, solution.minimumCost(5, 4, 15, 0, 0));
}

TEST(MinCostToAcquireRequiredItemsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(84755163318, solution.minimumCost(388168, 988887, 336014, 50411, 252237));
}

}