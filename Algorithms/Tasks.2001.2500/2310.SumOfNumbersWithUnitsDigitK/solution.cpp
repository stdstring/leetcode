#include <algorithm>
#include <optional>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumNumbers(int num, int k) const
    {
        if (num == 0)
            return 0;
        if (num < k)
            return -1;
        if ((num % 2 == 1) && (k % 2 == 0))
            return -1;
        std::vector<std::optional<size_t>> dp(num + 1, std::optional<size_t>());
        for (int number = k; number <= num; number += 10)
            dp[number] = 1;
        for (int current = k; current <= num; ++current)
        {
            if (!dp[current].has_value())
                continue;
            for (int number = k; (number <= current) && ((number + current) <= num); number += 10)
                dp[number + current] = std::min(dp[number + current].has_value() ? dp[number + current].value() : INT_MAX,
                                                  dp[current].value() + 1);
        }
        return dp[num].has_value() ? static_cast<int>(dp[num].value()) : -1;
    }
};

}

namespace SumOfNumbersWithUnitsDigitKTask
{

TEST(SumOfNumbersWithUnitsDigitKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumNumbers(58, 9));
    ASSERT_EQ(-1, solution.minimumNumbers(37, 2));
    ASSERT_EQ(0, solution.minimumNumbers(0, 7));
}

}