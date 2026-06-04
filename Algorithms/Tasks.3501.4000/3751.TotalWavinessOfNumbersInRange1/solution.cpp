#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int totalWaviness(int num1, int num2) const
    {
        constexpr size_t maxDigitsCount = 10;
        std::vector<int> digits(maxDigitsCount);
        int result = 0;
        for (int number = std::max(101, num1); number <= num2; ++number)
            result += countWaviness(number, digits);
        return result;
    }

private:
    [[nodiscard]] int countWaviness(int number, std::vector<int> &digits) const
    {
        int result = 0;
        size_t digitsCount = 0;
        for(; number > 0; number /= 10, ++digitsCount)
        {
            digits[digitsCount] = number % 10;
        }
        for (size_t index = 1; index < digitsCount - 1; ++index)
        {
            if ((digits[index] > digits[index - 1]) && (digits[index] > digits[index + 1]))
                ++result;
            if ((digits[index] < digits[index - 1]) && (digits[index] < digits[index + 1]))
                ++result;
        }
        return result;
    }
};

}

namespace TotalWavinessOfNumbersInRange1Task
{

TEST(TotalWavinessOfNumbersInRange1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.totalWaviness(120, 130));
    ASSERT_EQ(3, solution.totalWaviness(198, 202));
    ASSERT_EQ(2, solution.totalWaviness(4848, 4848));
}

TEST(TotalWavinessOfNumbersInRange1TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.totalWaviness(52525, 52525));
}

}