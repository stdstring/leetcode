#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isNumber(std::string const &s) const
    {
        std::string::const_iterator iterator = s.cbegin();
        skipWhitespaces(iterator, s.cend());
        if (!checkMantis(iterator, s.cend()))
            return false;
        if (iterator == s.cend())
            return true;
        if (*iterator == ' ')
        {
            skipWhitespaces(iterator, s.cend());
            return iterator == s.cend();
        }
        if (!checkExponent(iterator, s.cend()))
            return false;
        skipWhitespaces(iterator, s.cend());
        return iterator == s.cend();
    }

private:
    void skipWhitespaces(std::string::const_iterator &iterator, std::string::const_iterator end) const
    {
        while(iterator != end && *iterator == ' ')
            ++iterator;
    }

    bool checkMantis(std::string::const_iterator &iterator, std::string::const_iterator end) const
    {
        if (*iterator == '+' || *iterator == '-')
            ++iterator;
        int integralDigitsCount = 0;
        while(iterator != end && *iterator >= '0' && *iterator <= '9')
        {
            ++iterator;
            ++integralDigitsCount;
        }
        if (iterator == end)
            return integralDigitsCount > 0;
        if (*iterator == 'e')
            return integralDigitsCount > 0;
        if (*iterator == ' ')
            return true;
        if (*iterator != '.')
            return false;
        int fractionalDigitsCount = 0;
        ++iterator;
        while(iterator != end && *iterator >= '0' && *iterator <= '9')
        {
            ++iterator;
            ++fractionalDigitsCount;
        }
        if (iterator == end)
            return (integralDigitsCount > 0) || (fractionalDigitsCount > 0);
        if (*iterator == 'e')
            return (integralDigitsCount > 0) || (fractionalDigitsCount > 0);
        if (*iterator == ' ')
            return (integralDigitsCount > 0) || (fractionalDigitsCount > 0);
        return false;
    }

    bool checkExponent(std::string::const_iterator &iterator, std::string::const_iterator end) const
    {
        if (*iterator != 'e')
            return false;
        ++iterator;
        if (iterator == end)
            return false;
        if (*iterator == '+' || *iterator == '-')
            ++iterator;
        int digitsCount = 0;
        while(iterator != end && *iterator >= '0' && *iterator <= '9')
        {
            ++iterator;
            ++digitsCount;
        }
        if (digitsCount == 0)
            return false;
        if (iterator == end)
            return true;
        return *iterator == ' ';
    }
};

}

namespace ValidNumberTask
{

TEST(ValidNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isNumber("0"));
    ASSERT_EQ(true, solution.isNumber(" 0.1 "));
    ASSERT_EQ(false, solution.isNumber("abc"));
    ASSERT_EQ(false, solution.isNumber("1 a"));
    ASSERT_EQ(true, solution.isNumber("2e10"));
    ASSERT_EQ(true, solution.isNumber(" -90e3   "));
    ASSERT_EQ(false, solution.isNumber(" 1e"));
    ASSERT_EQ(false, solution.isNumber("e3"));
    ASSERT_EQ(true, solution.isNumber(" 6e-1"));
    ASSERT_EQ(false, solution.isNumber(" 99e2.5 "));
    ASSERT_EQ(true, solution.isNumber("53.5e93"));
    ASSERT_EQ(false, solution.isNumber(" --6 "));
    ASSERT_EQ(false, solution.isNumber("-+3"));
    ASSERT_EQ(false, solution.isNumber("95a54e53"));
}

TEST(ValidNumberTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isNumber(".1"));
    ASSERT_EQ(false, solution.isNumber("e"));
    ASSERT_EQ(false, solution.isNumber("0e"));
    ASSERT_EQ(true, solution.isNumber("3."));
    ASSERT_EQ(false, solution.isNumber("."));
    ASSERT_EQ(false, solution.isNumber(". "));
    ASSERT_EQ(true, solution.isNumber("46.e3"));
}

}