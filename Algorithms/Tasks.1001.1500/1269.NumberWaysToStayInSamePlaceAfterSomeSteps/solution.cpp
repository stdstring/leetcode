#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numWays(int steps, int arrLen) const
    {
        constexpr int modValue = 1000000007;
        const size_t dpSize = std::min(steps + 1, arrLen);
        const size_t maxDpIndex = dpSize - 1;
        std::vector<int> dpCurrent(dpSize, 0);
        std::vector<int> dpNext(dpSize, 0);
        dpCurrent[0] = 1;
        for (int step = 1; step <= steps; ++step)
        {
            for (size_t index = 0; index < dpSize; ++index)
            {
                dpNext[index] = (dpNext[index] + dpCurrent[index]) % modValue;
                if (index > 0)
                    dpNext[index - 1] = (dpNext[index - 1] + dpCurrent[index]) % modValue;
                if (index < maxDpIndex)
                    dpNext[index + 1] = (dpNext[index + 1] + dpCurrent[index]) % modValue;
            }
            std::swap(dpCurrent, dpNext);
            std::ranges::fill(dpNext, 0);
        }
        return dpCurrent[0];
    }
};

}

namespace NumberWaysToStayInSamePlaceAfterSomeStepsTask
{

TEST(NumberWaysToStayInSamePlaceAfterSomeStepsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.numWays(3, 2));
    ASSERT_EQ(2, solution.numWays(2, 4));
    ASSERT_EQ(8, solution.numWays(4, 2));
}

}