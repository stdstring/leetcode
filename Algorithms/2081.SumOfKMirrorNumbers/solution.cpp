#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long kMirror(int k, int n) const
    {
        long long base10Number = 1;
        std::vector<int> base10Digits({1});
        long long baseKNumber = 1;
        std::vector<int> baseKDigits({1});
        long long sum = 1;
        int count = 1;
        while (count < n)
        {
            if (base10Number < baseKNumber)
            {
                generateNext(base10Digits, 10);
                base10Number = createNumber(base10Digits, 10);
            }
            else
            {
                generateNext(baseKDigits, k);
                baseKNumber = createNumber(baseKDigits, k);
            }
            if (base10Number == baseKNumber)
            {
                sum += base10Number;
                ++count;
            }
        }
        return sum;
    }

private:
    [[nodiscard]] long long createNumber(std::vector<int> const &digits, int base) const
    {
        long long number = 0;
        for (const int digit : digits)
            number = number * base + digit;
        return number;
    }

    void generateInit(std::vector<int> &digits, size_t count) const
    {
        digits.clear();
        digits.reserve(count);
        digits.push_back(1);
        for (size_t number = 0; number < count - 2; ++number)
            digits.push_back(0);
        digits.push_back(1);
    }

    void generateNext(std::vector<int> &digits, int base) const
    {
        const size_t portionSize = digits.size() / 2;
        const size_t forwardStart = portionSize - (digits.size() % 2 == 0 ? 1 : 0);
        const size_t backwardStart = portionSize;
        for (size_t shift = 0; shift <= forwardStart; ++shift)
        {
            ++digits[forwardStart - shift];
            if (digits[forwardStart - shift] == base)
                digits[forwardStart - shift] = 0;
            digits[backwardStart + shift] = digits[forwardStart - shift];
            if (digits[forwardStart- +shift] != 0)
                return;
        }
        generateInit(digits, digits.size() + 1);
    }
};

}

namespace SumOfKMirrorNumbersTask
{

TEST(SumOfKMirrorNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(25, solution.kMirror(2, 5));
    ASSERT_EQ(499, solution.kMirror(3, 7));
    ASSERT_EQ(20379000, solution.kMirror(7, 17));
}

}