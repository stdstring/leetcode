#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countPrimeSetBits(int left, int right) const
    {
        constexpr size_t maxPrimeNumber = 32;
        std::vector<bool> primeNumbers(maxPrimeNumber + 1, false);
        for (const size_t primeNumber : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31})
            primeNumbers[primeNumber] = true;
        size_t result = 0;
        for (int number = left; number <= right; ++number)
        {
            const size_t numberOfSetBit = calcNumberOfSetBit(number);
            if (primeNumbers[numberOfSetBit])
                ++result;
        }
        return static_cast<int>(result);
    }

private:
    [[nodiscard]] size_t calcNumberOfSetBit(int number) const
    {
        size_t numberOfSetBit = 0;
        while (number > 0)
        {
            if ((number & 1) == 1)
                ++numberOfSetBit;
            number >>= 1;
        }
        return numberOfSetBit;
    }
};

}

namespace PrimeNumberOfSetBitsInBinReprTask
{

TEST(PrimeNumberOfSetBitsInBinReprTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.countPrimeSetBits(6, 10));
    ASSERT_EQ(5, solution.countPrimeSetBits(10, 15));
}

}