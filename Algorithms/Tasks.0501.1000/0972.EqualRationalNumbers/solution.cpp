#include <numeric>
#include <string>

#include "gtest/gtest.h"

namespace
{

struct NumberData
{
    NumberData(int integerPart, std::string const &nonRepeatingPart, std::string const &repeatingPart) : IntegerPart(integerPart), NonRepeatingPart(nonRepeatingPart), RepeatingPart(repeatingPart)
    {
    }

    int IntegerPart;
    std::string NonRepeatingPart;
    std::string RepeatingPart;
};

struct RationalNumber
{
    RationalNumber(int integerPart, int numerator, int denominator) : IntegerPart(integerPart), Numerator(numerator), Denominator(denominator)
    {
    }

    int IntegerPart;
    int Numerator;
    int Denominator;
};

class Solution
{
public:
    bool isRationalEqual(std::string const &s, std::string const &t) const
    {
        const NumberData sData(parseNumberData(s));
        const RationalNumber sNumber(createRationalNumber(sData));
        const NumberData tData(parseNumberData(t));
        const RationalNumber tNumber(createRationalNumber(tData));
        return sNumber.IntegerPart == tNumber.IntegerPart && sNumber.Numerator == tNumber.Numerator && sNumber.Denominator == tNumber.Denominator;
    }

private:
    NumberData parseNumberData(std::string const &source) const
    {
        const size_t pointPos = source.find('.');
        const int integerPart = stoi(pointPos == std::string::npos ? source : source.substr(0, pointPos));
        if (pointPos == std::string::npos)
            return NumberData(integerPart, "", "");
        const size_t repeatingPartStart = source.find('(');
        const std::string nonRepeatingPart(source.substr(pointPos + 1, (repeatingPartStart == std::string::npos ? source.size() : repeatingPartStart) - pointPos - 1));
        if (repeatingPartStart == std::string::npos)
            return NumberData(integerPart, nonRepeatingPart, "");
        const std::string repeatingPart(source.substr(repeatingPartStart + 1, source.size() - 1 - repeatingPartStart - 1));
        return NumberData(integerPart, nonRepeatingPart, repeatingPart);
    }

    RationalNumber createRationalNumber(NumberData const &data) const
    {
        if (data.NonRepeatingPart.empty() && data.RepeatingPart.empty())
            return RationalNumber(data.IntegerPart, 1, 1);
        if (data.RepeatingPart.empty())
        {
            const int numerator = stoi(data.NonRepeatingPart);
            const int denominator = calcTenPower(data.NonRepeatingPart.size());
            const int gcd = std::gcd(denominator, numerator);
            return RationalNumber(data.IntegerPart, numerator == 0 ? 1 : numerator / gcd, denominator / gcd);
        }
        // let x = int_part.non_repeating_part(repeating_part)
        // factor1 = 10 ^ non_repeating_part.size(), number1 = factor1 * x = factor1 * int_part + non_repeating_part.(repeating_part)
        // factor2 = factor1 * 10 ^ repeating_part.size(), number2 = factor2 * factor1 * x = factor2 * number1 = factor1 * factor2 * int_part + factor2 * non_repeating_part + repeating_part.(repeating_part)
        // number2 - number1 = (factor1 * factor2 * int_part + factor2 * non_repeating_part + repeating_part) - (factor1 * int_part + non_repeating_part) = (factor2 * factor1 - factor1) * x
        // so x = ((factor1 * factor2 * int_part + factor2 * non_repeating_part + repeating_part) - (factor1 * int_part + non_repeating_part)) / (factor2 * factor1 - factor1)
        const int64_t factor1 = calcTenPower(data.NonRepeatingPart.size());
        const int64_t number1 = data.IntegerPart * factor1 + (data.NonRepeatingPart.empty() ? 0 : stoi(data.NonRepeatingPart));
        const int64_t factor2 = calcTenPower(data.RepeatingPart.size());
        const int64_t number2 = number1 * factor2 + stoi(data.RepeatingPart);
        const int64_t delta1 = number2 - number1;
        const int64_t delta2 = factor1 * factor2 - factor1;
        const int64_t integerPart = delta1 / delta2;
        const int64_t fractionalPart = delta1 % delta2;
        const int64_t gcd = std::gcd(delta2, fractionalPart);
        const int64_t numerator = fractionalPart == 0 ? 1 : fractionalPart / gcd;
        const int64_t denominator = delta2 / gcd;
        return RationalNumber(static_cast<int>(integerPart), static_cast<int>(numerator), static_cast<int>(denominator));
    }

    int calcTenPower(size_t power) const
    {
        int result = 1;
        for (size_t step = 0; step < power; ++step)
            result *= 10;
        return result;
    }
};

}

namespace EqualRationalNumbersTask
{

TEST(EqualRationalNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isRationalEqual("0.(52)", "0.5(25)"));
    ASSERT_EQ(true, solution.isRationalEqual("0.1666(6)", "0.166(66)"));
    ASSERT_EQ(true, solution.isRationalEqual("0.9(9)", "1."));
}

TEST(EqualRationalNumbersTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isRationalEqual("1.0", "1"));
}

}