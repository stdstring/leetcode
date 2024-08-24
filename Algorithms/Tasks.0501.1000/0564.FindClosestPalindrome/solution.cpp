#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string nearestPalindromic(std::string const &n) const
    {
        if (n.size() == 1)
            return {static_cast<char>(n[0] - 1)};
        long long sourceNumber = std::stoll(n);
        std::string leftPartStr(n.substr(0, n.size() / 2 + ((n.size() % 2) == 1 ? 1 : 0)));
        long long leftPart = std::stoll(leftPartStr);
        std::vector<long long> palindromicNumbers(5, 0);
        palindromicNumbers[0] = generatePalindromic(leftPart, (n.size() % 2) == 1);
        // can create wrong answer, when leftPart = 9...9
        palindromicNumbers[1] = generatePalindromic(leftPart + 1, (n.size() % 2) == 1);
        // can create wrong answer, when leftPart = 10...0
        palindromicNumbers[2] = generatePalindromic(leftPart - 1, (n.size() % 2) == 1);
        // for fixing case, when leftPart = 9...9
        palindromicNumbers[3] = std::stoll(std::string(n.size() - 1, '9'));
        // for fixing case, when leftPart = 10...0
        palindromicNumbers[4] = std::stoll("1" + std::string(n.size() - 1, '0') + "1");
        long long bestPalindromic = 0;
        for (long long palindromic : palindromicNumbers)
        {
            if (palindromic == sourceNumber)
                continue;
            if (std::abs(sourceNumber - palindromic) < std::abs(sourceNumber - bestPalindromic))
                bestPalindromic = palindromic;
            else if ((std::abs(sourceNumber - palindromic) == std::abs(sourceNumber - bestPalindromic)))
                bestPalindromic = std::min(bestPalindromic, palindromic);
        }
        return std::to_string(bestPalindromic);
    }

private:
    [[nodiscard]] long long generatePalindromic(long long leftPart, bool isOdd) const
    {
        long long result = 0;
        long long leftFactor = 10;
        if (isOdd)
        {
            result = leftPart % 10;
            leftPart /= 10;
            leftFactor *= 10;
        }
        while (leftPart > 0)
        {
            long long digit = leftPart % 10;
            leftPart /= 10;
            result = digit * leftFactor + result * 10 + digit;
            if (leftPart > 0)
                leftFactor *= 100;
        }
        return result;
    }
};

}

namespace FindClosestPalindromeTask
{

TEST(FindClosestPalindromeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("121", solution.nearestPalindromic("123"));
    ASSERT_EQ("0", solution.nearestPalindromic("1"));
}

TEST(FindClosestPalindromeTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ("12321", solution.nearestPalindromic("12322"));
    ASSERT_EQ("123321", solution.nearestPalindromic("123322"));
    ASSERT_EQ("1001", solution.nearestPalindromic("999"));
    ASSERT_EQ("999", solution.nearestPalindromic("1000"));
    ASSERT_EQ("375573", solution.nearestPalindromic("375210"));
    ASSERT_EQ("12921", solution.nearestPalindromic("12932"));
    ASSERT_EQ("99799", solution.nearestPalindromic("99800"));
    ASSERT_EQ("1221", solution.nearestPalindromic("1234"));
}

TEST(FindClosestPalindromeTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("807045053350540708", solution.nearestPalindromic("807045053224792883"));
}

}