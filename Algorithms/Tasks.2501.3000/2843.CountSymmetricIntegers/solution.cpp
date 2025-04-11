#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countSymmetricIntegers(int low, int high) const
    {
        int digitCount = 2;
        int rangeStart = 10;
        int rangeEnd = 99;
        while (rangeEnd < low)
        {
            digitCount += 2;
            rangeStart *= 100;
            rangeEnd = 10 * rangeStart - 1;
        }
        size_t result = 0;
        for (int number = std::max(rangeStart, low); number <= high;)
        {
            if (isSymmetric(number, digitCount))
                ++result;
            ++number;
            if (number > rangeEnd)
            {
                digitCount += 2;
                rangeStart *= 100;
                rangeEnd = 10 * rangeStart - 1;
                number = rangeStart;
            }
        }
        return static_cast<int>(result);
    }

private:
    [[nodiscard]] bool isSymmetric(int number, int digitCount) const
    {
        int rightSum = 0;
        int leftSum = 0;
        const int partCount = digitCount / 2;
        for (int position = 0; position < digitCount; ++position)
        {
            const int digit = number % 10;
            (position  < partCount ? rightSum : leftSum) += digit;
            number /= 10;
        }
        return leftSum == rightSum;
    }
};

}

namespace CountSymmetricIntegersTask
{

TEST(CountSymmetricIntegersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.countSymmetricIntegers(1, 100));
    ASSERT_EQ(4, solution.countSymmetricIntegers(1200, 1230));
}

}