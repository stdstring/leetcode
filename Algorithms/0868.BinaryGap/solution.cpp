#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int binaryGap(int n) const
    {
        int maxGap = 0;
        int lastOnePos = -1;
        int currentPos = 0;
        while (n > 0)
        {
            if ((n & 1) == 1)
            {
                if (lastOnePos != -1)
                    maxGap = std::max(maxGap, currentPos - lastOnePos);
                lastOnePos = currentPos;
            }
            n >>= 1;
            ++currentPos;
        }
        return maxGap;
    }
};

}

namespace BinaryGapTask
{

TEST(BinaryGapTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.binaryGap(22));
    ASSERT_EQ(2, solution.binaryGap(5));
    ASSERT_EQ(1, solution.binaryGap(6));
    ASSERT_EQ(0, solution.binaryGap(8));
    ASSERT_EQ(0, solution.binaryGap(1));
}

}