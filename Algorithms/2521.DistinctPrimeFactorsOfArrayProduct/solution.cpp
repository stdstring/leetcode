#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int distinctPrimeFactors(std::vector<int> const &nums) const
    {
        std::unordered_set<int> primeFactors;
        std::unordered_set<int> knownNumbers;
        for (const int number : nums)
        {
            int current = number;
            while ((current > 1) && (knownNumbers.count(current) == 0))
            {
                knownNumbers.insert(current);
                int factor = calcSmallestPrimeFactor(current);
                primeFactors.insert(factor);
                knownNumbers.insert(factor);
                current = extractFactor(current, factor);
            }
        }
        return static_cast<int>(primeFactors.size());
    }

private:
    [[nodiscard]] int calcSmallestPrimeFactor(int number) const
    {
        if ((number % 2) == 0)
            return 2;
        int factor = 3;
        while (factor * factor <= number)
        {
            if ((number % factor) == 0)
                return factor;
            factor += 2;
        }
        return number;
    }

    [[nodiscard]] int extractFactor(int number, int factor) const
    {
        while ((number % factor) == 0)
            number /= factor;
        return number;
    }
};

}

namespace DistinctPrimeFactorsOfArrayProductTask
{

TEST(DistinctPrimeFactorsOfArrayProductTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.distinctPrimeFactors({2, 4, 3, 7, 10, 6}));
    ASSERT_EQ(1, solution.distinctPrimeFactors({2, 4, 8, 16}));
}

}