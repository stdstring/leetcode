#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numPrimeArrangements(int n) const
    {
        constexpr int modValue = 1000000007;
        const int primeNumbersCount = calcPrimeNumbersCount(n);
        const int nonPrimeNumbersCount = n - primeNumbersCount;
        return static_cast<int>(calcFactorial(primeNumbersCount, modValue) * calcFactorial(nonPrimeNumbersCount, modValue) % modValue);
    }

private:
    [[nodiscard]] int isPrime(int n) const
    {
        if (n == 1)
            return false;
        if (n == 2)
            return true;
        if (n % 2 == 0)
            return false;
        for (int factor = 3; factor * factor <= n; factor += 2)
        {
            if ((n % factor) == 0)
                return false;
        }
        return true;
    }

    [[nodiscard]] int calcPrimeNumbersCount(int n) const
    {
        if (n == 1)
            return 0;
        if (n == 2)
            return 1;
        int primeCount = 1;
        for (int number = 3; number <= n; number += 2)
        {
            if (isPrime(number))
                ++primeCount;
        }
        return primeCount;
    }

    [[nodiscard]] long long calcFactorial(long long n, long long modValue) const
    {
        long long factorial = 1;
        for (long long number = 1; number <= n; ++number)
            factorial = (factorial * number) % modValue;
        return factorial;
    }
};

}

namespace PrimeArrangementsTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.numPrimeArrangements(5));
    ASSERT_EQ(682289015, solution.numPrimeArrangements(100));
}

}