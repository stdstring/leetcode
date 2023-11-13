#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxProfit(std::vector<int> const &inventory, int orders) const
    {
        std::vector<int> balls(inventory);
        std::ranges::sort(balls, std::greater<int>());
        long long result = 0;
        for (size_t index = 1; index < balls.size(); ++index)
        {
            if (balls[index] == balls[index - 1])
                continue;
            const int portionLength = static_cast<int>(index);
            const int processedBalls = (balls[index - 1] - balls[index]) * portionLength;
            if (processedBalls >= orders)
            {
                result += calcProfitForBallsRemainder(orders, portionLength, balls[index - 1]);
                orders = 0;
                break;
            }
            result += 1LL * portionLength * calcNumberSum(balls[index] + 1, balls[index - 1]);
            orders -= processedBalls;
        }
        if (orders > 0)
            result += calcProfitForBallsRemainder(orders, static_cast<int>(balls.size()), balls.back());
        return static_cast<int>(result % 1000000007);
    }

private:
    [[nodiscard]] long long calcProfitForBallsRemainder(int balls, int portionLength, int topValue) const
    {
        long long result = 0;
        const int count = balls / portionLength;
        const int rest = balls % portionLength;
        if (count > 0)
            result += 1LL * portionLength * calcNumberSum(topValue - count + 1, topValue);
        result += 1LL * rest * (topValue - count);
        return result;
    }

    [[nodiscard]] long long calcNumberSum(int fromNumber, int toNumber) const
    {
        // arithmetic progression sum
        return 1LL * (fromNumber + toNumber) * (toNumber - fromNumber + 1) / 2;
    }
};

}

namespace SellDiminishingValuedColoredBallsTask
{

TEST(SellDiminishingValuedColoredBallsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(14, solution.maxProfit({2, 5}, 4));
    ASSERT_EQ(19, solution.maxProfit({3, 5}, 6));
}

}