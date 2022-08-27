#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDiff(int num) const
    {
        const std::vector<int> sourceDigits(getDigits(num));
        int maxNumber = num;
        size_t firstSmallDigitIndex = 0;
        for (; (firstSmallDigitIndex < sourceDigits.size()) && (sourceDigits[firstSmallDigitIndex] == 9); ++firstSmallDigitIndex){}
        if (firstSmallDigitIndex < sourceDigits.size())
            maxNumber = generateNumberAfterReplaceDigit(sourceDigits, sourceDigits[firstSmallDigitIndex], 9);
        int minNumber = num;
        if (sourceDigits.front() > 1)
            minNumber = generateNumberAfterReplaceDigit(sourceDigits, sourceDigits.front(), 1);
        else
        {
            size_t firstBigDigitIndex = 1;
            for (; (firstBigDigitIndex < sourceDigits.size()) && (sourceDigits[firstBigDigitIndex] <= 1); ++firstBigDigitIndex){}
            if (firstBigDigitIndex < sourceDigits.size())
                minNumber = generateNumberAfterReplaceDigit(sourceDigits, sourceDigits[firstBigDigitIndex], 0);
        }
        return maxNumber - minNumber;
    }

private:
    [[nodiscard]] std::vector<int> getDigits(int number) const
    {
        std::vector<int> digits;
        while (number > 0)
        {
            digits.push_back(number % 10);
            number /= 10;
        }
        std::reverse(digits.begin(), digits.end());
        return digits;
    }

    [[nodiscard]] int getNumber(std::vector<int> const &digits) const
    {
        int result = 0;
        for (const int digit : digits)
            result = 10 * result + digit;
        return result;
    }

    [[nodiscard]] int generateNumberAfterReplaceDigit(std::vector<int> const &sourceDigits, int oldDigit, int newDigit) const
    {
        std::vector<int> destDigits(sourceDigits);
        std::replace(destDigits.begin(), destDigits.end(), oldDigit, newDigit);
        return getNumber(destDigits);
    }
};

}

namespace MaxDiffFromChangingIntegerTask
{

TEST(MaxDiffFromChangingIntegerTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(888, solution.maxDiff(555));
    ASSERT_EQ(8, solution.maxDiff(9));
}

TEST(MaxDiffFromChangingIntegerTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(820000, solution.maxDiff(123456));
}

}