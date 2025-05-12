#include <array>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findEvenNumbers(std::vector<int> const &digits) const
    {
        // collect digits
        std::array<int, DigitCount> digitStorage;
        digitStorage.fill(0);
        for (const int digit : digits)
            ++digitStorage[digit];
        // traverse numbers
        std::vector<int> result;
        for (int number = 100; number < 1000; number += 2)
        {
            if (canCreate(number, digitStorage))
                result.emplace_back(number);
        }
        return result;
    }

private:
    static constexpr int DigitCount = 10;

    [[nodiscard]] bool canCreate(int number, std::array<int, DigitCount> const &digitStorage) const
    {
        // number's digits
        std::array<int, DigitCount> numberDigits;
        numberDigits.fill(0);
        for (;number > 0; number /= 10)
        {
            const int digit = number % 10;
            ++numberDigits[digit];
        }
        for (int digit = 0; digit < DigitCount; ++digit)
        {
            if (digitStorage[digit] < numberDigits[digit])
                return false;
        }
        return true;
    }
};

}

namespace Finding3DigitEvenNumbersTask
{

TEST(Finding3DigitEvenNumbersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({102, 120, 130, 132, 210, 230, 302, 310, 312, 320}), solution.findEvenNumbers({2, 1, 3, 0}));
    ASSERT_EQ(std::vector<int>({222, 228, 282, 288, 822, 828, 882}), solution.findEvenNumbers({2, 2, 8, 8, 2}));
    ASSERT_EQ(std::vector<int>(), solution.findEvenNumbers({3, 7, 5}));
}

}