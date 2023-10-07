#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numOfArrays(int n, int m, int k) const
    {
        constexpr int modValue = 1000000007;
        std::vector<long long> dpPrev(1ULL * m * k, 0);
        std::vector<long long> dpNext(1ULL * m * k, 0);
        // init
        for (int number = 1; number <= m; ++number)
            dpPrev[(number - 1) * k + 0] = 1;
        // dp
        for (size_t index = 0; index < static_cast<size_t>(n) - 1; ++index)
        {
            std::ranges::fill(dpNext, 0);
            for (int cost = 1; cost <= k; ++cost)
            {
                for (int maxNumber = 1; maxNumber <= m; ++maxNumber)
                {
                    dpNext[k * (maxNumber - 1) + (cost - 1)] = (dpNext[k * (maxNumber - 1) + (cost - 1)] + maxNumber * dpPrev[k * (maxNumber - 1) + (cost - 1)]) % modValue;
                    if (cost == k)
                        continue;
                    for (int number = maxNumber + 1; number <= m; ++number)
                        dpNext[k * (number - 1) + cost] = (dpNext[k * (number - 1) + cost] + dpPrev[k * (maxNumber - 1) + (cost - 1)]) % modValue;
                }
            }
            std::swap(dpNext, dpPrev);
        }
        // calc result
        long long result = 0;
        for (int number = 1; number <= m; ++number)
            result = (result + dpPrev[k * (number - 1) + (k - 1)]) % modValue;
        return static_cast<int>(result);
    }
};

}

namespace BuildArrayWhereMaxExactlyKCompTask
{

TEST(BuildArrayWhereMaxExactlyKCompTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.numOfArrays(2, 3, 1));
    ASSERT_EQ(0, solution.numOfArrays(5, 2, 3));
    ASSERT_EQ(1, solution.numOfArrays(9, 1, 1));
}

TEST(BuildArrayWhereMaxExactlyKCompTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(34549172, solution.numOfArrays(50, 100, 25));
}

}