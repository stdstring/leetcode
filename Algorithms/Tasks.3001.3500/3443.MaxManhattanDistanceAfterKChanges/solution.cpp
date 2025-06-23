#include <algorithm>
#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDistance(std::string const &s, int k) const
    {
        int result = 0;
        int nCount = 0;
        int sCount = 0;
        int wCount = 0;
        int eCount = 0;
        for (const char ch : s)
        {
            switch (ch)
            {
            case 'N':
                ++nCount;
                break;
            case 'S':
                ++sCount;
                break;
            case 'W':
                ++wCount;
                break;
            case 'E':
                ++eCount;
                break;
            default:
                throw std::logic_error("bad data");
            }
            result = std::max(result, calcMaxPossibleDistance(nCount, sCount, wCount, eCount, k));
        }
        return result;
    }

private:
    [[nodiscard]] int calcMaxPossibleDistance(int nCount, int sCount, int wCount, int eCount, int k) const
    {
        int distance = std::abs(nCount - sCount) + std::abs(wCount - eCount);
        if ((k > 0) && (nCount > 0) && (sCount > 0))
        {
            const int changes = std::min(k, std::min(nCount, sCount));
            distance += 2 * changes;
            k -= changes;
        }
        if ((k > 0) && (wCount > 0) && (eCount > 0))
        {
            const int changes = std::min(k, std::min(wCount, eCount));
            distance += 2 * changes;
            k -= changes;
        }
        return distance;
    }
};

}

namespace TwoSumTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxDistance("NWSE", 1));
    ASSERT_EQ(6, solution.maxDistance("NSWWEW", 3));
}

}