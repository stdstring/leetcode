#include <algorithm>
#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool primeSubOperation(std::vector<int> const &nums) const
    {
        bool isIncreasing = true;
        int maxNumber = nums[0];
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[index] <= nums[index - 1])
                isIncreasing = false;
            maxNumber = std::max(maxNumber, nums[index]);
        }
        if (isIncreasing)
            return true;
        std::set<int> primes(generatePrimes(maxNumber));
        int prevNumber = 0;
        for (const int number : nums)
        {
            if (number <= prevNumber)
                return false;
            const int delta = number - prevNumber;
            if (delta <= 2)
                prevNumber = number;
            else
            {
                auto iterator = std::prev(primes.lower_bound(delta));
                prevNumber = number - *iterator;
            }
        }
        return true;
    }

private:
    [[nodiscard]] std::set<int> generatePrimes(int maxNumber) const
    {
        if (maxNumber < 2)
            return {};
        std::set<int> primes;
        primes.emplace(2);
        for (int number = 3; number <= maxNumber; number += 2)
        {
            if (isPrimeNumber(number, primes))
                primes.emplace(number);
        }
        return primes;
    }

    [[nodiscard]] bool isPrimeNumber(int number, std::set<int> const &primes) const
    {
        for (const int prime : primes)
        {
            if ((prime * prime) > number)
                break;
            if ((number % prime) == 0)
                return false;
        }
        return true;
    }
};

}

namespace PrimeSubtractionOperationTask
{

TEST(PrimeSubtractionOperationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.primeSubOperation({4, 9, 6, 10}));
    ASSERT_EQ(true, solution.primeSubOperation({6, 8, 11, 12}));
    ASSERT_EQ(false, solution.primeSubOperation({5, 8, 3}));
}

}