#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int atMostNGivenDigitSet(std::vector<std::string> const &digits, int n) const
    {
        std::vector<int> digitsSource(digits.size(), 0);
        std::transform(digits.cbegin(), digits.cend(), digitsSource.begin(), [](std::string const &digit){ return digit[0] - '0'; });
        size_t totalCount = 0;
        int factor = 1;
        std::vector<size_t> rangeCounts;
        int rest = n;
        while (rest >= 10)
        {
            rangeCounts.push_back(rangeCounts.empty() ? digitsSource.size() : rangeCounts.back() * digitsSource.size());
            totalCount += rangeCounts.back();
            factor *= 10;
            rest /= 10;
        }
        size_t rangeRIndex = 0;
        while (n >= 10)
        {
            const std::pair<size_t, bool> digitsCountData = calcDigitsCount(digitsSource, n / factor, false);
            totalCount += digitsCountData.first * rangeCounts[rangeCounts.size() - 1 - rangeRIndex];
            if (!digitsCountData.second)
                return static_cast<int>(totalCount);
            n = n % factor;
            factor /= 10;
            ++rangeRIndex;
        }
        totalCount += calcDigitsCount(digitsSource, n, true).first;
        return static_cast<int>(totalCount);
    }

private:
    [[nodiscard]] std::pair<size_t, bool> calcDigitsCount(std::vector<int> const &digits, int maxDigit, bool includeMaxDigit) const
    {
        size_t digitsCount = 0;
        bool containsMaxDigit = false;
        for (const int digit : digits)
        {
            if (digit == maxDigit)
                containsMaxDigit = true;
            if ((digit > maxDigit) || (!includeMaxDigit && digit == maxDigit))
                break;
            ++digitsCount;
        }
        return {digitsCount, containsMaxDigit};
    }
};

}

namespace NumbersAtMostNGivenDigitSetTask
{

TEST(NumbersAtMostNGivenDigitSetTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(20, solution.atMostNGivenDigitSet({"1", "3", "5", "7"}, 100));
    ASSERT_EQ(29523, solution.atMostNGivenDigitSet({"1", "4", "9"}, 1000000000));
    ASSERT_EQ(1, solution.atMostNGivenDigitSet({"7"}, 8));
}

}