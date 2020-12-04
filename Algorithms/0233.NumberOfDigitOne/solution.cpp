#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countDigitOne(int n) const
    {
        // Description :
        // 0 .. 9 - quantity of 1 is 1
        // 00 .. 99 - quantity of 1 is 10 + 10 * 1 = 20
        // 000 .. 999 - quantity of 1 is 100 + 10 * 20 = 300
        // 0000 .. 9999 - quantity of 1 is 1000 + 10 * 300 = 4000
        // for full ranges:
        // 0..0 .. 9..9 (n digits) = 10..0 (n digits, quantity of 0 is n - 1) + 10 * prev_range_value
        // for non full ranges
        // 1x..z - (1 + x..z) + prev_range_value + count(x..z)
        // ax..z (a > 1, n digits) - 10..0 (n digits, quantity of 0 is n - 1) + a * prev_range_value + count(x..z)
        if (n < 0)
            return 0;
        std::vector<size_t> rangesCount;
        std::vector<size_t> tenPowers;
        fillRangesData(n, rangesCount, tenPowers);
        return static_cast<int>(calcDigitOne(n, rangesCount, tenPowers, rangesCount.size() - 1));
    }

private:
    void fillRangesData(size_t n, std::vector<size_t> &rangesCount, std::vector<size_t> &tenPowers) const
    {
        rangesCount.push_back(1);
        tenPowers.push_back(1);
        size_t rangeStart = 10;
        size_t rangeEnd = 99;
        while (rangeEnd < n)
        {
            tenPowers.push_back(rangeStart);
            rangesCount.push_back(rangeStart + 10 * rangesCount.back());
            rangeStart *= 10;
            rangeEnd = 10 * rangeEnd + 9;
        }
    }

    size_t calcDigitOne(size_t n, std::vector<size_t> const &rangesCount, std::vector<size_t> const &tenPowers, size_t prevIndex) const
    {
        if (n < 10)
            return n > 0 ? 1 : 0;
        size_t tenPower = 10 * tenPowers[prevIndex];
        while (n < tenPower)
        {
            --prevIndex;
            tenPower /= 10;
        }
        const size_t olderDigit = n / tenPower;
        const size_t rest = n % tenPower;
        if (olderDigit == 1)
            return (1 + rest) + rangesCount[prevIndex] + calcDigitOne(rest, rangesCount, tenPowers, prevIndex - 1);
        return tenPower + olderDigit * rangesCount[prevIndex] + calcDigitOne(rest, rangesCount, tenPowers, prevIndex - 1);
    }
};

}

namespace NumberOfDigitOneTask
{

TEST(NumberOfDigitOneTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.countDigitOne(13));
}

TEST(NumberOfDigitOneTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(316, solution.countDigitOne(1011));
    ASSERT_EQ(0, solution.countDigitOne(-1));
}

}