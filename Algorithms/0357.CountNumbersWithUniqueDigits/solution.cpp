#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countNumbersWithUniqueDigits(int n) const
    {
        // take account 0
        int numbers = 1;
        for (int digitsCount = 1; digitsCount <= n; ++digitsCount)
        {
            int numbersCountWithSize = 9;
            for (int digitPos = 1; digitPos < digitsCount; ++digitPos)
                numbersCountWithSize *= (10 - digitPos);
            numbers += numbersCountWithSize;
        }
        return numbers;
    }
};

}

namespace CountNumbersWithUniqueDigitsTask
{

TEST(CountNumbersWithUniqueDigitsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(91, solution.countNumbersWithUniqueDigits(2));
}

}