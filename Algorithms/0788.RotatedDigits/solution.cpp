#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int rotatedDigits(int n) const
    {
        const std::vector<int> rotateResult({0, 1, 5, -1, -1, 2, 9, -1, 8, 6});
        size_t goodNumberCount = 0;
        int factor = 10;
        for (int number = 1; number <= n; ++number)
        {
            if (factor <= n)
                factor *= 10;
            int numberRest = number;
            int currentFactor = factor / 10;
            int rotatedNumber = 0;
            bool goodNumber = true;
            while (numberRest > 0 && goodNumber)
            {
                const int digit = numberRest / currentFactor;
                goodNumber = rotateResult[digit] != -1;
                if (goodNumber)
                    rotatedNumber += (rotateResult[digit] * currentFactor);
                numberRest %= currentFactor;
                currentFactor /= 10;
            }
            if (goodNumber && (rotatedNumber != number))
                ++goodNumberCount;
        }
        return static_cast<int>(goodNumberCount);
    }
};

}

namespace RotatedDigitsTask
{

TEST(RotatedDigitsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.rotatedDigits(10));
    ASSERT_EQ(0, solution.rotatedDigits(1));
    ASSERT_EQ(1, solution.rotatedDigits(2));
}

}