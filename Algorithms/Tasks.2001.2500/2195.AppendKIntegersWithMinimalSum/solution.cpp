#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimalKSum(std::vector<int> const &nums, int k) const
    {
        const size_t expectedNumsCount = k;
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        long long appendedNumsSum = 0;
        size_t appendedNumsCount = 0;
        int last = 0;
        for (const int number : numbers)
        {
            if (last < number)
            {
                const int start = last + 1;
                const size_t delta = 0LL + number - start;
                const size_t count = std::min(delta, expectedNumsCount - appendedNumsCount);
                appendedNumsSum += calcRangeSum(start, count);
                appendedNumsCount += count;
            }
            if (expectedNumsCount == appendedNumsCount)
                break;
            last = number;
        }
        appendedNumsSum += calcRangeSum(last + 1, expectedNumsCount - appendedNumsCount);
        return appendedNumsSum;
    }

private:
    [[nodiscard]] long long calcRangeSum(int start, size_t count) const
    {
        return static_cast<long long>(count * (2LL * start + 1LL * (count - 1)) / 2);
    }
};

}

namespace AppendKIntegersWithMinimalSumTask
{

TEST(AppendKIntegersWithMinimalSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.minimalKSum({1, 4, 25, 10, 25}, 2));
    ASSERT_EQ(25, solution.minimalKSum({5, 6}, 6));
}

TEST(AppendKIntegersWithMinimalSumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(5000000150000000, solution.minimalKSum({1}, 100000000));
}

}