#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> kthPalindrome(std::vector<int> const &queries, int intLength) const
    {
        const int halfLength = intLength / 2 + intLength % 2;
        int maxQuery = 9;
        for (int digit = 1; digit < halfLength; ++digit)
            maxQuery *= 10;
        --maxQuery;
        std::vector<long long> palindromes(queries.size(), -1);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            const int query = queries[index] - 1;
            if (query <= maxQuery)
                palindromes[index] = intLength == 1 ? 0LL + query + 1 : generatePalindrome(intLength, query);
        }
        return palindromes;
    }

private:
    [[nodiscard]] long long generatePalindrome(int intLength, int query) const
    {
        std::vector<int> digits(intLength, 0);
        const size_t halfRight = intLength / 2;
        const size_t halfLeft = halfRight - (intLength % 2 == 0 ? 1 : 0);
        for (size_t shift = 0; shift <= halfLeft; ++shift)
        {
            const int digit = query % 10;
            query /= 10;
            digits[halfLeft - shift] = digits[halfRight + shift] = digit;
        }
        ++digits.front();
        ++digits.back();
        long long palindrome = 0;
        for (const int digit : digits)
            palindrome = 10LL * palindrome + digit;
        return palindrome;
    }
};

}

namespace FindPalindromeWithFixedLengthTask
{

TEST(FindPalindromeWithFixedLengthTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({101, 111, 121, 131, 141, 999}), solution.kthPalindrome({1, 2, 3, 4, 5, 90}, 3));
    ASSERT_EQ(std::vector<long long>({1111, 1331, 1551}), solution.kthPalindrome({2, 4, 6}, 4));
}

TEST(FindPalindromeWithFixedLengthTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, 9, 8}),
              solution.kthPalindrome({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 9, 8}, 1));
    ASSERT_EQ(std::vector<long long>({-1, 55, 44, 11, -1, -1, 33, 77, 66, 33, -1, -1, 55}),
              solution.kthPalindrome({392015495, 5, 4, 1, 425320571, 565971690, 3, 7, 6, 3, 506222280, 468075092, 5}, 2));
}

}