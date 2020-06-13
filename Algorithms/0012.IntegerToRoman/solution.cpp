#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string intToRoman(int num) const
    {
        std::string result;
        const int thousands = num / 1000;
        for (int counter = 1; counter <= thousands; ++counter)
            result.push_back('M');
        const int hundreds = (num % 1000) / 100;
        result.append(mRomanHundreds[hundreds]);
        const int tens = (num % 100) / 10;
        result.append(mRomanTens[tens]);
        const int ones = num % 10;
        result.append(mRomanOnes[ones]);
        return result;
    }

private:
    std::string mRomanOnes[10] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    std::string mRomanTens[10] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    std::string mRomanHundreds[10] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
};

}

namespace IntegerToRomanTask
{

TEST(StringToIntegerTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("III", solution.intToRoman(3));
    ASSERT_EQ("IV", solution.intToRoman(4));
    ASSERT_EQ("IX", solution.intToRoman(9));
    ASSERT_EQ("LVIII", solution.intToRoman(58));
    ASSERT_EQ("MCMXCIV", solution.intToRoman(1994));
}

}