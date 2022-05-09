#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canConstruct(std::string const &s, int k) const
    {
        const size_t palindromeCount = k;
        if (s.size() < palindromeCount)
            return false;
        if (s.size() == palindromeCount)
            return true;
        constexpr size_t alphabetSize = 26;
        constexpr size_t alphabetStart = 'a';
        std::array<size_t, alphabetSize> letterData{};
        letterData.fill(0);
        for (const char ch : s)
            ++letterData[ch - alphabetStart];
        size_t oddCountLetters = 0;
        for (const size_t count : letterData)
        {
            if (count % 2 == 1)
                ++oddCountLetters;
        }
        return oddCountLetters <= palindromeCount;
    }
};

}

namespace ConstructKPalindromeStringsTask
{

TEST(ConstructKPalindromeStringsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canConstruct("annabelle", 2));
    ASSERT_EQ(false, solution.canConstruct("leetcode", 3));
    ASSERT_EQ(true, solution.canConstruct("true", 4));
}

}