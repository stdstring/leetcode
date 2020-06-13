#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int rangeBitwiseAnd(int m, int n) const
    {
        int result = 0;
        int shift = 0;
        while (n > 0)
        {
            const int mValue = m & 1;
            if ((mValue ^ (n & 1)) == 1)
                result = 0;
            else
                result |= (mValue << shift);
            m >>= 1;
            n >>= 1;
            ++shift;
        }
        return result;
    }
};

}

namespace BitwiseAndOfNumbersRangeTask
{

TEST(BitwiseAndOfNumbersRangeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.rangeBitwiseAnd(5, 7));
    ASSERT_EQ(0, solution.rangeBitwiseAnd(0, 1));
}

TEST(BitwiseAndOfNumbersRangeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(5, solution.rangeBitwiseAnd(5, 5));
    ASSERT_EQ(2147483647, solution.rangeBitwiseAnd(2147483647, 2147483647));
}

}