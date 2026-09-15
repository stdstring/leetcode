#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxPalindromes(std::string const &s, int k) const
    {
        if (k == 1)
            return static_cast<int>(s.size());
        size_t palindromeCount = 0;
        for (size_t index = 0; index <= s.size() - k;)
        {
            if (isPalindrome(s, index, index + k - 1))
            {
                ++palindromeCount;
                index += k;
            }
            else if (((index + k) < s.size()) && isPalindrome(s, index, index + k))
            {
                ++palindromeCount;
                index += (k + 1);
            }
            else
                ++index;
        }
        return static_cast<int>(palindromeCount);
    }

private:
    [[nodiscard]] bool isPalindrome(std::string const &source, size_t start, size_t end) const
    {
        for (; start < end; ++start, --end)
        {
            if (source[start] != source[end])
                return false;
        }
        return true;
    }
};

}

namespace MaxNumberPalindromeSubstringsTask
{

TEST(MaxNumberPalindromeSubstringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxPalindromes("abaccdbbd", 3));
    ASSERT_EQ(0, solution.maxPalindromes("adbcda", 2));
}

TEST(MaxNumberPalindromeSubstringsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.maxPalindromes("wctqaietbwbwbtelubvbbvbulohknbsuylyusbqdxcelecxmomcozocmojusycwcys", 7));
}

}