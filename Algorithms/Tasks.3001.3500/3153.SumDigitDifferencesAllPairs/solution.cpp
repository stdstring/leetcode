#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long sumDigitDifferences(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        const long long numberCount = static_cast<long long>(numbers.size());
        long long result = 0;
        while (numbers.front() > 0)
        {
            std::vector<long long> digits(10, 0);
            for (int &number : numbers)
            {
                ++digits[number % 10];
                number /= 10;
            }
            for (const long long digitCount : digits)
                result += digitCount * (numberCount - digitCount);
        }
        return result / 2;
    }
};

}

namespace SumDigitDifferencesAllPairsTask
{

TEST(SumDigitDifferencesAllPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.sumDigitDifferences({13, 23, 12}));
    ASSERT_EQ(0, solution.sumDigitDifferences({10, 10, 10, 10}));
}

}