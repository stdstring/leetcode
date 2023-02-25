#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isThree(int n) const
    {
        // 1, n
        size_t divisorsCount = 2;
        int divisor = 2;
        for (; divisor * divisor < n; ++divisor)
        {
            if (n % divisor == 0)
                return false;
        }
        return divisor * divisor == n;
    }
};

}

namespace ThreeDivisorsTask
{

TEST(ThreeDivisorsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isThree(2));
    ASSERT_EQ(true, solution.isThree(4));
}

}