#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumSwap(int num) const
    {
        // number to digits
        std::vector<int> digits;
        while (num > 0)
        {
            digits.push_back(num % 10);
            num /= 10;
        }
        // swap
        for (size_t rstart = 0; rstart < digits.size() - 1; ++rstart)
        {
            const int startDigit = digits[digits.size() - 1 - rstart];
            if (startDigit == 9)
                continue;
            size_t rbest = digits.size();
            for (size_t rcurrent = rstart + 1; rcurrent < digits.size(); ++rcurrent)
            {
                const int currentDigit = digits[digits.size() - 1 - rcurrent];
                if ((startDigit < currentDigit) && ((rbest == digits.size()) || (digits[digits.size() - 1 - rbest] <= currentDigit)))
                    rbest = rcurrent;
            }
            if (rbest != digits.size())
            {
                std::swap(digits[digits.size() - 1 - rstart], digits[digits.size() - 1 - rbest]);
                break;
            }
        }
        // digits to number
        int result = 0;
        int factor = 1;
        for (const int digit : digits)
        {
            result += (digit * factor);
            factor *= 10;
        }
        return result;
    }
};

}

namespace MaximumSwapTask
{

TEST(MaximumSwapTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(7236, solution.maximumSwap(2736));
    ASSERT_EQ(9973, solution.maximumSwap(9973));
}

}