#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimumCost(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        const int numberCount = static_cast<int>(numbers.size());
        int medianValue;
        if ((numberCount % 2) == 0)
        {
            const auto left = std::next(numbers.begin(), numberCount / 2 - 1);
            std::ranges::nth_element(numbers, left);
            const int leftValue = *left;
            const auto right = std::next(numbers.begin(), numberCount / 2);
            std::ranges::nth_element(numbers, right);
            const int rightValue = *right;
            medianValue = (leftValue + rightValue) / 2;
        }
        else
        {
            const auto current = std::next(numbers.begin(), numberCount / 2);
            std::ranges::nth_element(numbers, current);
            medianValue = *current;
        }
        if (isPalindrome(medianValue))
            return calcCost(numbers, medianValue);
        long long cost = LLONG_MAX;
        if (medianValue > 1)
            cost = std::min(cost, calcCost(numbers, moveToPalindrome(medianValue - 1, -1)));
        cost = std::min(cost, calcCost(numbers, moveToPalindrome(medianValue + 1, 1)));
        return cost;
    }

private:
    [[nodiscard]] bool isPalindrome(int number) const
    {
        if (number < 10)
            return true;
        constexpr size_t maxDigitCount = 10;
        std::vector<int> digits;
        digits.reserve(maxDigitCount);
        while (number > 0)
        {
            digits.emplace_back(number % 10);
            number /= 10;
        }
        for (size_t start = 0, end = digits.size() - 1; start < end; ++start, --end)
        {
            if (digits[start] != digits[end])
                return false;
        }
        return true;
    }

    [[nodiscard]] int moveToPalindrome(int number, int delta) const
    {
        while (!isPalindrome(number))
            number += delta;
        return number;
    }

    [[nodiscard]] long long calcCost(std::vector<int> const &numbers, int value) const
    {
        return std::accumulate(numbers.cbegin(), numbers.cend(), 0LL, [value](long long acc, int number) { return acc + 1LL * std::abs(number - value); });
    }
};

}

namespace MinCostMakeArrayEqualindromicTask
{

TEST(MinCostMakeArrayEqualindromicTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.minimumCost({1, 2, 3, 4, 5}));
    ASSERT_EQ(11, solution.minimumCost({10, 12, 13, 14, 15}));
    ASSERT_EQ(22, solution.minimumCost({22, 33, 22, 33, 22}));
}

TEST(MinCostMakeArrayEqualindromicTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2532, solution.minimumCost({107, 846, 886, 574, 104, 863, 476, 259, 338, 647}));
}

}