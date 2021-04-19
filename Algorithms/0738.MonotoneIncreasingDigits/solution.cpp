#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int monotoneIncreasingDigits(int n) const
    {
        std::vector<int> digits;
        while (n > 0)
        {
            int digit = n % 10;
            digits.push_back(digit);
            n /= 10;
        }
        int result = 0;
        bool nineMode = false;
        for (std::vector<int>::const_reverse_iterator current = digits.crbegin(); current != digits.crend(); ++current)
        {
            result *= 10;
            const int currentDigit = *current;
            const int nextDigit = findNextDigit(current, digits.crend());
            if (nineMode)
                result += 9;
            else if (currentDigit > nextDigit)
            {
                nineMode = true;
                result += (currentDigit - 1);
            }
            else
                result += currentDigit;
        }
        return result;
    }

private:
    int findNextDigit(std::vector<int>::const_reverse_iterator current, std::vector<int>::const_reverse_iterator end) const
    {
        const int currentDigit = *current;
        int nextDigit = *current;
        while ((current != end) && (currentDigit == nextDigit))
        {
            nextDigit = *current;
            ++current;
        }
        return nextDigit;
    }
};

}

namespace MonotoneIncreasingDigitsTask
{

TEST(MonotoneIncreasingDigitsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(9, solution.monotoneIncreasingDigits(10));
    ASSERT_EQ(1234, solution.monotoneIncreasingDigits(1234));
    ASSERT_EQ(299, solution.monotoneIncreasingDigits(332));
}

TEST(MonotoneIncreasingDigitsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(119, solution.monotoneIncreasingDigits(120));
}

}