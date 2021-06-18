#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int primePalindrome(int n) const
    {
        if (n == 1 || n == 2)
            return 2;
        std::vector<int> palindrome(findSmallestPalindrome(n));
        int palindromeNumber = constructNumber(palindrome);
        while (!isPrime(palindromeNumber))
        {
            generateNextPalindrome(palindrome);
            palindromeNumber = constructNumber(palindrome);
        }
        return palindromeNumber;
    }

private:
    std::vector<int> findSmallestPalindrome(int n) const
    {
        std::vector<int> digits;
        int number = n;
        while (number != 0)
        {
            digits.push_back(number % 10);
            number /= 10;
        }
        if (digits.back() % 2 == 0)
        {
            const int digit = digits.back() + 1;
            for (size_t index = 0; index < digits.size(); ++index)
                digits[index] = 0;
            digits.front() = digits.back() = digit;
        }
        else
        {
            size_t left = 0;
            size_t right = digits.size() - 1;
            while (left < right)
            {
                digits[left] = digits[right];
                ++left;
                --right;
            }
            if (constructNumber(digits) < n)
                generateNextPalindrome(digits);
        }
        return digits;
    }

    void generateNextPalindrome(std::vector<int> &digits) const
    {
        size_t left = digits.size() / 2 - (digits.size() % 2 == 0 ? 1 : 0);
        for(size_t right = digits.size() / 2; right < digits.size(); ++right)
        {
            if (digits[right] == 9)
                digits[left] = digits[right] = 0;
            else
            {
                digits[left] += (left == 0 ? 2 : 1);
                if (left != right)
                    digits[right] += (left == 0 ? 2 : 1);
                return;
            }
            if (left > 0)
                --left;
        }
        digits[left] = 1;
        digits.push_back(1);
    }

    int constructNumber(std::vector<int> const &digits) const
    {
        int number = 0;
        for (int digit : digits)
            number = number * 10 + digit;
        return number;
    }

    bool isPrime(int n) const
    {
        for (int factor = 3; factor * factor <= n; factor += 2)
        {
            if (n % factor == 0)
                return false;
        }
        return true;
    }
};

}

namespace PrimePalindromeTask
{

TEST(PrimePalindromeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(7, solution.primePalindrome(6));
    ASSERT_EQ(11, solution.primePalindrome(8));
    ASSERT_EQ(101, solution.primePalindrome(13));
}

TEST(PrimePalindromeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.primePalindrome(1));
    ASSERT_EQ(2, solution.primePalindrome(2));
}

}