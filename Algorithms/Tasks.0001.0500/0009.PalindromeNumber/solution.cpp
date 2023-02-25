#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isPalindrome(int x) const
    {
        if (x == 0)
            return true;
        if (x < 0)
            return false;
        int digitCount = 0;
        int divider = 0;
        calcNumberData(x, digitCount, divider);
        while (digitCount > 1)
        {
            const int firstDigit = x / divider;
            x = x % divider;
            const int lastDigit = x % 10;
            x = x / 10;
            if (firstDigit != lastDigit)
                return false;
            divider /= 100;
            digitCount -= 2;
        }
        return true;
    }

private:
    void calcNumberData(int number, int &digitCount, int &divider) const
    {
        long long topBorder = 1;
        while (number > 0)
        {
            number /= 10;
            ++digitCount;
            topBorder *= 10;
        }
        divider = static_cast<int>(topBorder / 10);
    }
};

}

namespace PalindromeNumberTask
{

TEST(PalindromeNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isPalindrome(121));
    ASSERT_EQ(false, solution.isPalindrome(-121));
    ASSERT_EQ(false, solution.isPalindrome(10));
}

TEST(PalindromeNumberTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isPalindrome(1000021));
}

}