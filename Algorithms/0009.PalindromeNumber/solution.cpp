#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isPalindrome(int x) const
    {
        if (x == 0)
            return true;
        if (x < 0)
            return false;
        std::vector<int> digits;
        while (x > 0)
        {
            digits.push_back(x % 10);
            x /= 10;
        }
        if (digits.back() == 0)
            return false;
        for (size_t index = 0; index < digits.size() / 2; ++index)
        {
            if (digits[index] != digits[digits.size() - 1 - index])
                return false;
        }
        return true;
    }
};

}

namespace PalindromeNumberTask
{

TEST(StringToIntegerTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isPalindrome(121));
    ASSERT_EQ(false, solution.isPalindrome(-121));
    ASSERT_EQ(false, solution.isPalindrome(10));
}

}