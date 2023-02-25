#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isStrictlyPalindromic(int n) const
    {
        for (int base = 2; base <= n - 2; ++base)
        {
            if (!isPalindrome(getDigits(n, base)))
                return false;
        }
        return true;
    }

private:
    [[nodiscard]] std::vector<int> getDigits(int n, int base) const
    {
        std::vector<int> digits;
        while (n > 0)
        {
            digits.push_back(n % base);
            n /= base;
        }
        return digits;
    }

    [[nodiscard]] bool isPalindrome(std::vector<int> const &digits) const
    {
        for (size_t left = 0, right = digits.size() - 1; left < right; ++left, --right)
        {
            if (digits[left] != digits[right])
                return false;
        }
        return true;
    }
};

}

namespace StrictlyPalindromicNumberTask
{

TEST(StrictlyPalindromicNumberTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.isStrictlyPalindromic(9));
    ASSERT_EQ(false, solution.isStrictlyPalindromic(4));
}

}