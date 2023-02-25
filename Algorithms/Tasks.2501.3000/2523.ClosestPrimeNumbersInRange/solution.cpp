#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> closestPrimes(int left, int right) const
    {
        const int delta = right - left;
        if (delta == 0)
            return {-1, -1};
        if (delta == 1)
            return {left == 2 ? left : -1, left == 2 ? right : -1};
        if ((delta == 2) && (left % 2 == 0))
            return {-1, -1};
        if (left <= 2)
            return { 2, 3 };
        if (left % 2 == 0)
            ++left;
        int prime1 = -1;
        int prime2 = -1;
        int bestPrime1 = -1;
        int bestPrime2 = -1;
        for (int current = left; current <= right; current += 2)
        {
            if (isOddNumberPrime(current))
            {
                (prime1 == -1 ? prime1 : prime2) = current;
                if ((prime2 != -1) && ((bestPrime1 == -1) || ((prime2 - prime1) < (bestPrime2 - bestPrime1))))
                {
                    bestPrime1 = prime1;
                    bestPrime2 = prime2;
                }
                if (prime2 != -1)
                    prime1 = prime2;
            }
        }
        return {bestPrime1, bestPrime2};
    }

private:
    [[nodiscard]] bool isOddNumberPrime(int number) const
    {
        for (int divider = 3; divider * divider <= number; divider += 2)
        {
            if (number % divider == 0)
                return false;
        }
        return true;
    }
};

}

namespace ClosestPrimeNumbersInRangeTask
{

TEST(ClosestPrimeNumbersInRangeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({11, 13}), solution.closestPrimes(10, 19));
    ASSERT_EQ(std::vector<int>({-1, -1}), solution.closestPrimes(4, 6));
}

TEST(ClosestPrimeNumbersInRangeTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 3}), solution.closestPrimes(1, 1000000));
}

}