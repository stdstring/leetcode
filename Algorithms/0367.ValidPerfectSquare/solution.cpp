#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isPerfectSquare(int num) const
    {
        int left = 1;
        // int(sqrt(2^31 - 1)) == 46340
        int right = 46340;
        if (num == 1)
            return true;
        if ((right * right) == num)
            return true;
        if ((right * right) < num)
            return false;
        while ((right - left) > 1)
        {
            const int middle = (left + right) / 2;
            if ((middle * middle) == num)
                return true;
            if ((middle * middle) < num)
                left = middle;
            else
                right = middle;
        }
        return num == (right * right);
    }
};

}

namespace ValidPerfectSquareTask
{

TEST(ValidPerfectSquareTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isPerfectSquare(16));
    ASSERT_EQ(false, solution.isPerfectSquare(14));
}

}