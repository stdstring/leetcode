#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countPrimes(int n)
    {
        if (n <= 2)
            return 0;
        // 2
        int count = 1;
        std::vector<int> sieve;
        sieve.resize(calcSieveSize(n), 1);
        for(int number = 3; number < n; number += 2)
        {
            if (sieve[calcIndex(number)] == 1)
            {
                ++count;
                erasePrimeFactors(number, n, sieve);
            }
        }
        return count;
    }

private:
    int calcSieveSize(int n)
    {
        return (n / 2) - 1;
    }

    int calcIndex(int number)
    {
        return (number - 3) / 2;
    }

    void erasePrimeFactors(long long prime, int n, std::vector<int> &sieve)
    {
        for(long long number = prime * prime; number < n; number += 2 * prime)
        {
            sieve[calcIndex(number)] = 0;
        }
    }
};

}

namespace CountPrimesTask
{

TEST(CountPrimesTaskTests, Examples)
{
    Solution solution;
    ASSERT_EQ(4, solution.countPrimes(10));
}

TEST(CountPrimesTaskTests, FromWrongAnswers)
{
    Solution solution;
    ASSERT_EQ(41537, solution.countPrimes(499979));
    ASSERT_EQ(0, solution.countPrimes(2));
    ASSERT_EQ(0, solution.countPrimes(0));
}

}