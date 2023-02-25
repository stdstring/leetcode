#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int nextBeautifulNumber(int n) const
    {
        const std::vector<std::vector<std::vector<int>>> combinations({{{1}},
                                                                       {{2}},
                                                                       {{1, 2}, {3}},
                                                                       {{1, 3}, {4}},
                                                                       {{1, 4}, {2, 3}, {5}},
                                                                       {{1, 2, 3}, {1, 5}, {2, 4}, {6}},
                                                                       {{1, 2, 4}}});
        const size_t digitCount = getDigitCount(n);
        int result = createNumber(generateDigits(combinations[digitCount - (digitCount == combinations.size() ? 1 : 0)].front()));
        if (digitCount == combinations.size())
            return result;
        for (std::vector<int> const &combination : combinations[digitCount - 1])
        {
            std::vector<int> digits(generateDigits(combination));
            bool isValid = true;
            while (isValid)
            {
                int number = createNumber(digits);
                if (number > n)
                    result = std::min(result, number);
                isValid = std::next_permutation(digits.begin(), digits.end());
            }
        }
        return result;
    }

private:
    [[nodiscard]] int getDigitCount(int n) const
    {
        int digitCount = 1;
        for (; n > 9; n /= 10)
            ++digitCount;
        return digitCount;
    }

    [[nodiscard]] std::vector<int> generateDigits(std::vector<int> const &combination) const
    {
        std::vector<int> digits;
        for (int digit : combination)
        {
            for (size_t index = 0; index < digit; ++index)
                digits.push_back(digit);
        }
        return digits;
    }

    [[nodiscard]] int createNumber(std::vector<int> const &digits) const
    {
        int number = 0;
        for (const int digit : digits)
            number = 10 * number + digit;
        return number;
    }
};

}

namespace NextGreaterNumericallyBalancedNumberTask
{

TEST(NextGreaterNumericallyBalancedNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(22, solution.nextBeautifulNumber(1));
    ASSERT_EQ(1333, solution.nextBeautifulNumber(1000));
    ASSERT_EQ(3133, solution.nextBeautifulNumber(3000));
}

}