#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfWays(int startPos, int endPos, int k) const
    {
        const int totalSteps = k;
        const int endPosSteps = std::abs(endPos - startPos);
        if (k < endPosSteps)
            return 0;
        const int stepsRest = totalSteps - endPosSteps;
        if ((stepsRest % 2) != 0)
            return 0;
        const int stepsBackward = stepsRest / 2;
        // we need in C(totalSteps, stepsBackward);
        return calcBinomialCoeff(totalSteps, stepsBackward);
    }

private:
    [[nodiscard]] int calcBinomialCoeff(int maxN, int kValue) const
    {
        // C(n,k) = C(n-1,k-1) + C(n-1, k)
        // C(n,k) = C(n,n-k)
        constexpr int modValue = 1000000007;
        std::vector<int> current({1});
        for (int n = 1; n <= maxN; ++n)
        {
            std::vector<int> next(n + 1, 1);
            for (int k = 1; k <= n / 2; ++k)
            {
                next[k] = (current[k] + current[k - 1]) % modValue;
                next[n - k] = next[k];
            }
            std::swap(current, next);
        }
        return current[kValue];
    }
};

}

namespace NumberWaysReachPositionAfterKStepsTask
{

TEST(NumberWaysReachPositionAfterKStepsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numberOfWays(1, 2, 3));
    ASSERT_EQ(0, solution.numberOfWays(2, 5, 10));
}

TEST(NumberWaysReachPositionAfterKStepsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.numberOfWays(671, 669, 4));
    ASSERT_EQ(0, solution.numberOfWays(1, 10, 3));
}

}