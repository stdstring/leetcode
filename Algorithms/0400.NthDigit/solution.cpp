#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findNthDigit(int n) const
    {
        if (n <= 9)
            return n;
        size_t digitNumber = n;
        size_t numberRangeStart = 1;
        size_t numberRangeSize = 9;
        size_t numberDigitsCount = 1;
        size_t numberRangeDigitsCount = numberDigitsCount * numberRangeSize;
        while (digitNumber > numberRangeDigitsCount)
        {
            digitNumber -= numberRangeDigitsCount;
            numberRangeStart *= 10;
            numberRangeSize *= 10;
            ++numberDigitsCount;
            numberRangeDigitsCount = numberDigitsCount * numberRangeSize;
        }
        const size_t numberIndex = digitNumber - 1;
        size_t number = numberRangeStart + numberIndex / numberDigitsCount;
        const size_t digitIndex = numberIndex % numberDigitsCount;
        for (size_t index = numberDigitsCount - 1; index > digitIndex; --index)
            number /= 10;
        return static_cast<int>(number % 10);
    }
};

}

namespace NthDigitTask
{

TEST(NthDigitTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.findNthDigit(3));
    ASSERT_EQ(0, solution.findNthDigit(11));
}

TEST(NthDigitTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(1, solution.findNthDigit(10));
}

}