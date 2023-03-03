#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int smallestValue(int n) const
    {
        if (n <= 5)
            return n;
        auto [sieve, primes] = calcPrimes(n);
        while (((n % 2) == 0) || !sieve[getOddNumberIndex(n)])
            n = transformNumber(n, primes);
        return n;
    }

private:
    [[nodiscard]] std::pair<std::vector<bool>, std::vector<int>> calcPrimes(int n) const
    {
        std::vector<int> primes;
        primes.emplace_back(2);
        const size_t sieveSize = n / 2 - (n % 2 == 0 ? 1 : 0);
        std::vector<bool> sieve(sieveSize, true);
        for (int current = 3; current <= n; current += 2)
        {
            if (!sieve[getOddNumberIndex(current)])
                continue;
            primes.emplace_back(current);
            for (long long number = 1LL * current * current; number <= n; number += 2LL * current)
                sieve[getOddNumberIndex(static_cast<int>(number))] = false;
        }
        return {sieve, primes};
    }

    [[nodiscard]] std::pair<int, size_t> extractFactor(int n, int factor) const
    {
        if ((n % factor) != 0)
            return {n, 0};
        size_t count = 0;
        while ((n % factor) == 0)
        {
            ++count;
            n /= factor;
        }
        return {n, count};
    }

    [[nodiscard]] int transformNumber(int n, std::vector<int> const &primes) const
    {
        int result = 0;
        for (const int prime : primes)
        {
            if (n == prime)
            {
                result += prime;
                break;
            }
            auto [rest, count] = extractFactor(n, prime);
            result += static_cast<int>(prime * count);
            n = rest;
            if (n == 1)
                break;
        }
        return result;
    }

    [[nodiscard]] size_t getOddNumberIndex(int n) const
    {
        return n / 2 - 1;
    }
};

}

namespace SmallestValueAfterPrimeFactorsSumReplacingTask
{

TEST(SmallestValueAfterPrimeFactorsSumReplacingTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.smallestValue(15));
    ASSERT_EQ(3, solution.smallestValue(3));
}

TEST(SmallestValueAfterPrimeFactorsSumReplacingTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.smallestValue(4));
    ASSERT_EQ(13, solution.smallestValue(13));
    ASSERT_EQ(7, solution.smallestValue(99951));
}

}