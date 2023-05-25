#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double new21Game(int n, int k, int maxPts) const
    {
        // When the game ends, the point is between k and k - 1 + maxPts
        // What is the probability that the the point is less than n?
        //   -If n is greater than k - 1 + maxPts, probability is 1
        //   - If n is less than k, probability is 0
        //   If maxPts == 3 and we want to find the probability to get a 5
        //     - You can get a card with value 1, 2, or 3 with equal probability(1 / 3)
        //     - If you had a 4 and you get a 1: prob(4) * (1 / 3)
        //     - If you had a 3 and you get a 2 : prob(3) * (1 / 3)
        //     - If you had a 2 and you get a 3 : prob(2) * (1 / 3)
        //     - If you had a 1, you can never reach a 5 in the next draw
        //     - prob(5) = prob(4) / 3 + prob(3) / 3 + prob(2) / 3
        // To generalize :
        //   The probability to get point K is
        //   p(k) = p(k - 1) / maxPts + p(k - 2) / maxPts + p(k - 3) / maxPts + ... p(maxPts - maxPts) / maxPts
        //   let wsum = p(k - 1) + p(k - 2) + ... + p(k - maxPts)
        //   p(k) = wsum / maxPts
        if ((k == 0) || (n >= (k + maxPts - 1)))
            return 1.0;
        std::vector<double> dp(n + 1, 0);
        dp[0] = 1.0;
        double wsum = 1.0;
        double result = 0.0;
        for (int current = 1; current <= n; ++current)
        {
            dp[current] = wsum / maxPts;
            if (current < k)
                wsum += dp[current];
            else
                result += dp[current];
            if (current - maxPts >= 0)
                wsum -= dp[current - maxPts];
        }
        return result;
    }
};

}

namespace New21GameTask
{

TEST(New21GameTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_NEAR(1.0, solution.new21Game(10, 1, 10), 0.00001);
    ASSERT_NEAR(0.6, solution.new21Game(6, 1, 10), 0.00001);
    ASSERT_NEAR(0.73278, solution.new21Game(21, 17, 10), 0.00001);
}

}