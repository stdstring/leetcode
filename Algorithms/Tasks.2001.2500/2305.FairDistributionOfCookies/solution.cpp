#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int distributeCookies(std::vector<int> const &cookies, int k) const
    {
        const int maskCount = 1 << cookies.size();
        std::vector<int> cookieSums(maskCount, 0);
        for (int mask = 1; mask < maskCount; ++mask)
        {
            int currentSum = 0;
            for (size_t index = 0; index < cookies.size(); ++index)
            {
                if ((mask & (1 << index)) != 0)
                    currentSum += cookies[index];
            }
            cookieSums[mask] = currentSum;
        }
        std::vector<int> currentDp(cookieSums);
        for (int child = 1; child < k; ++child)
        {
            std::vector<int> nextDp(maskCount, INT_MAX);
            for (int currentMask = 1; currentMask < maskCount; ++currentMask)
            {
                for (int nextMask = 1; nextMask < maskCount; ++nextMask)
                {
                    if ((currentMask & nextMask) > 0)
                        continue;
                    int maxValue = std::max(currentDp[currentMask], cookieSums[nextMask]);
                    nextDp[currentMask | nextMask] = std::min(nextDp[currentMask | nextMask], maxValue);
                }
            }
            std::swap(currentDp, nextDp);
        }
        return currentDp.back();
    }
};

}

namespace FairDistributionOfCookiesTask
{

TEST(FairDistributionOfCookiesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(31, solution.distributeCookies({8, 15, 10, 20, 8}, 2));
    ASSERT_EQ(7, solution.distributeCookies({6, 1, 3, 2, 2, 4, 1, 2}, 3));
}

}