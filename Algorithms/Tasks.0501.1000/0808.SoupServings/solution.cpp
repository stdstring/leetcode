#include <iterator>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double soupServings(int n) const
    {
        // we know, that if n >= 5000, then abs(1 - Probability) < 0.00001
        constexpr int maxProcessingPortion = 4999;
        if (n > maxProcessingPortion)
            return 1.0;
        constexpr int portionQuantum = 25;
        const size_t portionCount = n / portionQuantum + ((n % portionQuantum) == 0 ? 0 : 1);
        std::vector<std::vector<double>> dp(portionCount + 1, std::vector<double>(portionCount + 1, 0.0));
        dp.back().back() = 1.0;
        for (size_t firstIndex = portionCount; firstIndex > 0; --firstIndex)
        {
            for (size_t secondIndex = portionCount; secondIndex > 0; --secondIndex)
            {
                if (dp[firstIndex][secondIndex] == 0.0)
                    continue;
                // Serve 100 ml of soup A and 0 ml of soup B
                dp[firstIndex >= 4 ? firstIndex - 4 : 0][secondIndex] += 0.25 * dp[firstIndex][secondIndex];
                // Serve 75 ml of soup A and 25 ml of soup B
                dp[firstIndex >= 3 ? firstIndex - 3 : 0][secondIndex >= 1 ? secondIndex - 1 : 0] += 0.25 * dp[firstIndex][secondIndex];
                // Serve 50 ml of soup A and 50 ml of soup B
                dp[firstIndex >= 2 ? firstIndex - 2 : 0][secondIndex >= 2 ? secondIndex - 2 : 0] += 0.25 * dp[firstIndex][secondIndex];
                // Serve 25 ml of soup A and 75 ml of soup B
                dp[firstIndex >= 1 ? firstIndex - 1 : 0][secondIndex >= 3 ? secondIndex - 3 : 0] += 0.25 * dp[firstIndex][secondIndex];
            }
        }
        return std::accumulate(std::next(dp[0].cbegin(), 1), dp[0].cend(), 0.5 * dp[0][0]);
    }
};

}

namespace SoupServingsTask
{

TEST(SoupServingsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_NEAR(0.62500, solution.soupServings(50), 0.00001);
    ASSERT_NEAR(0.71875, solution.soupServings(100), 0.00001);
}

TEST(SoupServingsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_NEAR(1.00000, solution.soupServings(5000), 0.00001);
}

}