#include <array>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countGoodNumbers(long long n) const
    {
        // even digits = 0, 2, 4, 6, 8
        const int evenCount = 5;
        std::array<int, 10> evenCountPowers(generatePowers(evenCount));
        // odd digits = 2, 3, 5, 7
        const int oddCount = 4;
        std::array<int, 10> oddCountPowers(generatePowers(oddCount));
        const long long evenPosCount = pow(evenCount, n / 2 + n % 2, evenCountPowers);
        const long long oddPosCount = pow(oddCount, n / 2, oddCountPowers);
        return static_cast<int>((evenPosCount * oddPosCount) % ModValue);
    }

private:
    static constexpr int ModValue = 1000000007;

    std::array<int, 10> generatePowers(int factor) const
    {
        std::array<int, 10> powers{};
        powers[0] = 1;
        for (size_t power = 1; power <= 9; ++power)
            powers[power] = powers[power - 1] * factor;
        return powers;
    }

    long long pow10(long long value) const
    {
        long long result = value;
        for (int power = 2; power <= 10; ++power)
            result = (result * value) % ModValue;
        return result;
    }

    long long pow(int base, long long exponent, std::array<int, 10> const &powers) const
    {
        if (exponent == 0)
            return 1;
        const size_t digit = exponent % 10;
        const long long prevValue = pow(base, exponent / 10, powers);
        return (pow10(prevValue) * powers[digit]) % ModValue;
    }
};

}

namespace CountGoodNumbersTask
{

TEST(CountGoodNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.countGoodNumbers(1));
    ASSERT_EQ(400, solution.countGoodNumbers(4));
    ASSERT_EQ(564908303, solution.countGoodNumbers(50));
}

}