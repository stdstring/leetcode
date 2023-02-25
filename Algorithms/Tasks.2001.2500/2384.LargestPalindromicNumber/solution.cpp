#include <array>
#include <optional>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string largestPalindromic(std::string const &num) const
    {
        constexpr size_t alphabetSize = 10;
        constexpr size_t alphabetStart = '0';
        std::array<size_t, alphabetSize> digitData{};
        digitData.fill(0);
        for (const char ch : num)
            ++digitData[ch - alphabetStart];
        std::string result;
        std::optional<char> middleDigit;
        for (size_t rIndex = 0; rIndex < alphabetSize; ++rIndex)
        {
            const size_t index = alphabetSize - 1 - rIndex;
            char digit = static_cast<char>(alphabetStart + index);
            if ((digit != alphabetStart) || !result.empty())
                result.append(digitData[index] / 2, digit);
            if (((digitData[index] % 2) == 1) && !middleDigit.has_value())
                middleDigit = digit;
        }
        if (result.empty() && !middleDigit.has_value())
            middleDigit = '0';
        const std::string rightPart(result.crbegin(), result.crend());
        if (middleDigit.has_value())
            result.append(1, middleDigit.value());
        result.append(rightPart);
        return result;
    }
};

}

namespace LargestPalindromicNumberTask
{

TEST(LargestPalindromicNumberTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("7449447", solution.largestPalindromic("444947137"));
    ASSERT_EQ("9", solution.largestPalindromic("00009"));
}

TEST(LargestPalindromicNumberTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("6006", solution.largestPalindromic("6006"));
    ASSERT_EQ("0", solution.largestPalindromic("00"));
    ASSERT_EQ("10001", solution.largestPalindromic("00011"));
}

}