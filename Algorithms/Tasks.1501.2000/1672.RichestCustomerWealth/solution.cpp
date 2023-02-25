#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumWealth(std::vector<std::vector<int>> const &accounts) const
    {
        int result = 0;
        for (std::vector<int> const &account : accounts)
            result = std::max(result, std::accumulate(account.cbegin(), account.cend(), 0));
        return result;
    }
};

}

namespace RichestCustomerWealthTask
{

TEST(RichestCustomerWealthTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.maximumWealth({{1, 2, 3}, {3, 2, 1}}));
    ASSERT_EQ(10, solution.maximumWealth({{1, 5}, {7, 3}, {3, 5}}));
    ASSERT_EQ(17, solution.maximumWealth({{2, 8, 7}, {7, 1, 3}, {1, 9, 5}}));
}

}