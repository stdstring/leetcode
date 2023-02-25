#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int romanToInt(std::string const &s) const
    {
        int result = 0;
        for (size_t index = 0; index < s.size(); ++index)
            result += (isSubtraction(s, index) ? -getRomanSymbolValue(s[index]) : getRomanSymbolValue(s[index]));
        return result;
    }

private:
    bool isSubtraction(std::string const &s, size_t index) const
    {
        return index < (s.size() - 1) && getRomanSymbolValue(s[index]) < getRomanSymbolValue(s[index + 1]);
    }

    int getRomanSymbolValue(char romanSymbol) const
    {
        switch (romanSymbol)
        {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
        }
    }
};

}

namespace RomanToIntegerTask
{

TEST(RomanToIntegerTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.romanToInt("III"));
    ASSERT_EQ(4, solution.romanToInt("IV"));
    ASSERT_EQ(9, solution.romanToInt("IX"));
    ASSERT_EQ(58, solution.romanToInt("LVIII"));
    ASSERT_EQ(1994, solution.romanToInt("MCMXCIV"));
}

}