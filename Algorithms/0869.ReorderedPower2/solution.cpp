#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool reorderedPowerOf2(int n) const
    {
        if (n == MaxValue)
            return false;
        int power2 = 1;
        int rangeEnd = 10;
        while (rangeEnd <= n)
        {
            power2 *= 2;
            if (power2 > rangeEnd)
                rangeEnd *= 10;
        }
        const std::vector<int> nDigits(getSortedDigits(n));
        while (power2 < rangeEnd)
        {
            std::vector<int> power2Digits(getSortedDigits(power2));
            if (compareSortedDigits(nDigits, power2Digits))
                return true;
            power2 *= 2;
        }
        return false;
    }

private:
    static constexpr int MaxValue = 1000000000;

    std::vector<int> getSortedDigits(int n) const
    {
        std::vector<int> digits;
        while (n > 0)
        {
            digits.push_back(n % 10);
            n /= 10;
        }
        std::sort(digits.begin(), digits.end());
        return digits;
    }

    bool compareSortedDigits(std::vector<int> const &digits1, std::vector<int> const &digits2) const
    {
        for (size_t index = 0; index < digits1.size(); ++index)
        {
            if (digits1[index] != digits2[index])
                return false;
        }
        return true;
    }
};

}

namespace ReorderedPower2Task
{

TEST(ReorderedPower2TaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.reorderedPowerOf2(1));
    ASSERT_EQ(false, solution.reorderedPowerOf2(10));
    ASSERT_EQ(true, solution.reorderedPowerOf2(16));
    ASSERT_EQ(false, solution.reorderedPowerOf2(24));
    ASSERT_EQ(true, solution.reorderedPowerOf2(46));
}

}