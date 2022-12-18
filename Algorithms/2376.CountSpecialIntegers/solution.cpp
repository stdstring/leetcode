#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countSpecialNumbers(int n) const
    {
        constexpr size_t totalDigitCount = 10;
        size_t count = 0;
        const std::vector<int> digits(getDigits(n));
        for (size_t digitsCount = 1; digitsCount < digits.size(); ++digitsCount)
            count += calcCombinationCount(digitsCount, 10, false);
        std::vector<bool> usedDigits(totalDigitCount, false);
        const size_t lastIndex = digits.size() - 1;
        for (size_t index = 0; index < digits.size(); ++index)
        {
            for (int digit = index == 0 ? 1 : 0; index < lastIndex ? digit < digits[index] : digit <= digits[index]; ++digit)
            {
                if (!usedDigits[digit])
                    count += calcCombinationCount(digits.size() - 1 - index, totalDigitCount - index - 1, true);
            }
            if (usedDigits[digits[index]])
                break;
            usedDigits[digits[index]] = true;
        }
        return static_cast<int>(count);
    }

private:
    [[nodiscard]] std::vector<int> getDigits(int n) const
    {
        std::vector<int> digits;
        while (n > 0)
        {
            digits.emplace_back(n % 10);
            n /= 10;
        }
        std::reverse(digits.begin(), digits.end());
        return digits;
    }

    [[nodiscard]] size_t calcCombinationCount(size_t numberSize, size_t restDigitsCount, bool firstZeroAvailable) const
    {
        size_t count = 1;
        for (size_t numberDigit = 1; numberDigit <= numberSize; ++numberDigit)
        {
            count *= (numberDigit == 1 && !firstZeroAvailable ? restDigitsCount - 1 : restDigitsCount);
            --restDigitsCount;
        }
        return count;
    }
};

}

namespace CountSpecialIntegersTask
{

TEST(CountSpecialIntegersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(19, solution.countSpecialNumbers(20));
    ASSERT_EQ(5, solution.countSpecialNumbers(5));
    ASSERT_EQ(110, solution.countSpecialNumbers(135));
}

}