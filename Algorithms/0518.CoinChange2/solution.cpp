#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int change(int amount, std::vector<int> const &coins) const
    {
        if (amount == 0)
            return 1;
        if (coins.empty())
            return 0;
        std::vector<size_t> waysCountData(amount, 0);
        for (int coin: coins)
        {
            if (coin > amount)
                continue;
            ++waysCountData[coin - 1];
            for (int sum = 1; sum <= amount - coin; ++sum)
            {
                if (waysCountData[sum - 1] != 0)
                    waysCountData[sum + coin - 1] += waysCountData[sum - 1];
            }
        }
        return waysCountData.back();
    }
};

}

namespace CoinChange2Task
{

TEST(CoinChange2TaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.change(5, {1, 2, 5}));
    ASSERT_EQ(0, solution.change(3, {2}));
    ASSERT_EQ(1, solution.change(10, {10}));
}

TEST(CoinChange2TaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(1, solution.change(0, {}));
    ASSERT_EQ(1, solution.change(100, {1, 101, 102, 103}));
}

}