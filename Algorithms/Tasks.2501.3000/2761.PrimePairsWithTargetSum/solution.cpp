#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> findPrimePairs(int n) const
    {
        if (n <= 3)
            return {};
        if (n == 4)
            return {{2, 2}};
        if ((n % 2) == 1)
            return isOddPrime(n - 2) ? std::vector<std::vector<int>>({{2, n - 2}}) : std::vector<std::vector<int>>();
        std::set<int> oddPrimes;
        for (int divider = 3; divider < n; divider += 2)
        {
            if (isOddPrime(divider, oddPrimes))
                oddPrimes.emplace(divider);
        }
        std::vector<std::vector<int>> result;
        for (const int oddPrime : oddPrimes)
        {
            if ((2 * oddPrime) > n)
                break;
            if (oddPrimes.contains(n - oddPrime))
                result.emplace_back(std::vector<int>({oddPrime, n-oddPrime}));
        }
        return result;
    }

private:
    [[nodiscard]] bool isOddPrime(int n) const
    {
        for (int divider = 3; divider * divider <= n; divider += 2)
        {
            if ((n % divider) == 0)
                return false;
        }
        return true;
    }

    [[nodiscard]] bool isOddPrime(int n, std::set<int> const &oddPrimes) const
    {
        for (const int oddPrime : oddPrimes)
        {
            if (oddPrime * oddPrime > n)
                return true;
            if ((n % oddPrime) == 0)
                return false;
        }
        return true;
    }
};

}

namespace PrimePairsWithTargetSumTask
{

TEST(PrimePairsWithTargetSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 7}, {5, 5}}), solution.findPrimePairs(10));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.findPrimePairs(2));
}

TEST(PrimePairsWithTargetSumTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{2, 2}}), solution.findPrimePairs(4));
}

}