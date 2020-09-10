#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findComplement(int num) const
    {
        int result = 0;
        bool hasOneBit = false;
        for (int bit = 31; bit >= 0; --bit)
        {
            if ((num & (1 << bit)) == 0)
            {
                if (hasOneBit)
                    result |= (1 << bit);
            }
            else
                hasOneBit = true;
        }
        return result;
    }
};

}

namespace NumberComplementTask
{

TEST(NumberComplementTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findComplement(5));
    ASSERT_EQ(0, solution.findComplement(1));
}

}