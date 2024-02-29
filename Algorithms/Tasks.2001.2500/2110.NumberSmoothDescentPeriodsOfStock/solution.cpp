#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long getDescentPeriods(std::vector<int> const &prices) const
    {
        long long count = 0;
        size_t start = 0;
        for (size_t index = 0; index < prices.size(); ++index)
        {
            if ((index != start) && (prices[index - 1] != (prices[index] + 1)))
            {
                count += calcArithProgressionSum(static_cast<int>(index - start));
                start = index;
            }
        }
        count += calcArithProgressionSum(static_cast<int>(prices.size() - start));
        return count;
    }

private:
    [[nodiscard]] long long calcArithProgressionSum(int count) const
    {
        return (1LL + count) * count / 2;
    }
};

}

namespace NumberSmoothDescentPeriodsOfStockTask
{

TEST(NumberSmoothDescentPeriodsOfStockTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.getDescentPeriods({3, 2, 1, 4}));
    ASSERT_EQ(4, solution.getDescentPeriods({8, 6, 7, 7}));
    ASSERT_EQ(1, solution.getDescentPeriods({1}));
}

}