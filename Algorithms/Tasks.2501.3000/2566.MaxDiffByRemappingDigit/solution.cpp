#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minMaxDifference(int num) const
    {
        const std::vector<int> sourceDigits(getDigits(num));
        const int maxNumber = calcMaxNumber(sourceDigits);
        const int minNumber = calcMinNumber(sourceDigits);
        return maxNumber - minNumber;
    }

private:
    [[nodiscard]] std::vector<int> getDigits(int number) const
    {
        std::vector<int> digits;
        while (number > 0)
        {
            digits.emplace_back(number % 10);
            number /= 10;
        }
        std::ranges::reverse(digits);
        return digits;
    }

    [[nodiscard]] int calcMaxNumber(std::vector<int> const &sourceDigits) const
    {
        int number = 0;
        int remappedDigit = 9;
        for (const int digit : sourceDigits)
        {
            if ((remappedDigit == 9) && (digit != 9))
                remappedDigit = digit;
            number = 10 * number + (digit == remappedDigit ? 9 : digit);
        }
        return number;
    }

    [[nodiscard]] int calcMinNumber(std::vector<int> const &sourceDigits) const
    {
        int number = 0;
        for (const int digit : sourceDigits)
            number = 10 * number + (digit == sourceDigits[0] ? 0 : digit);
        return number;
    }
};

}

namespace MaxDiffByRemappingDigitTask
{

TEST(MaxDiffByRemappingDigitTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(99009, solution.minMaxDifference(11891));
    ASSERT_EQ(99, solution.minMaxDifference(90));
}

}