#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxIceCream(std::vector<int> const &costs, int coins) const
    {
        std::vector<int> sortedCosts(costs);
        std::sort(sortedCosts.begin(), sortedCosts.end());
        size_t result = 0;
        for (const int cost : sortedCosts)
        {
            if (cost > coins)
                break;
            coins -= cost;
            ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace MaxIceCreamBarsTask
{

TEST(MaxIceCreamBarsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxIceCream({1, 3, 2, 4, 1}, 7));
    ASSERT_EQ(0, solution.maxIceCream({10, 6, 8, 7, 7, 8}, 5));
    ASSERT_EQ(6, solution.maxIceCream({1, 6, 3, 1, 2, 5}, 20));
}

}