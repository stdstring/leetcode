#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumSwap(std::string const &s1, std::string const &s2) const
    {
        int unmatchedX1 = 0;
        int unmatchedY1 = 0;
        int unmatchedX2 = 0;
        int unmatchedY2 = 0;
        for (size_t index = 0; index < s1.size(); ++index)
        {
            if (s1[index] == s2[index])
                continue;
            ++(s1[index] == 'x' ? unmatchedX1 : unmatchedY1);
            ++(s2[index] == 'x' ? unmatchedX2 : unmatchedY2);
        }
        if (((unmatchedX1 + unmatchedY1) % 2) != 0)
            return -1;
        int swapCount = 0;
        const int swapXX1YY2 = 2 * (std::min(unmatchedX1, unmatchedY2) / 2);
        swapCount += (swapXX1YY2 / 2);
        unmatchedX1 -= swapXX1YY2;
        unmatchedY2 -= swapXX1YY2;
        const int swapYY1XX2 = 2 * (std::min(unmatchedY1, unmatchedX2) / 2);
        swapCount += (swapYY1XX2 / 2);
        unmatchedY1 -= swapYY1XX2;
        unmatchedX2 -= swapYY1XX2;
        if ((unmatchedX1 != unmatchedY1) || (unmatchedX2 != unmatchedY2))
            return -1;
        swapCount += 2 * unmatchedX1;
        return swapCount;
    }
};

}

namespace MinSwapsMakeStringsEqualTask
{

TEST(MinSwapsMakeStringsEqualTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minimumSwap("xx", "yy"));
    ASSERT_EQ(2, solution.minimumSwap("xy", "yx"));
    ASSERT_EQ(-1, solution.minimumSwap("xx", "xy"));
}

}