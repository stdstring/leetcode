#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string fractionAddition(std::string const &expression) const
    {
        size_t index = 0;
        int resultNumerator = 0;
        int resultDenominator = 0;
        readFraction(expression, index, resultNumerator, resultDenominator);
        while (index < expression.size())
        {
            const char currentOp = expression[index++];
            int numerator = 0;
            int denominator = 0;
            readFraction(expression, index, numerator, denominator);
            resultNumerator = denominator * resultNumerator + (currentOp == '+' ? 1 : -1) * resultDenominator * numerator;
            resultDenominator *= denominator;
            if (resultNumerator == 0)
                resultDenominator = 1;
            else
            {
                const int gcd = calcGCD(resultNumerator, resultDenominator);
                resultNumerator /= gcd;
                resultDenominator /= gcd;
            }
        }
        return std::to_string(resultNumerator) + "/" + std::to_string(resultDenominator);
    }

private:
    void readFraction(std::string const &expression, size_t &index, int &numerator, int &denominator) const
    {
        // read numerator
        numerator = 0;
        int numeratorSign = 1;
        if (expression[index] == '-')
        {
            numeratorSign = -1;
            ++index;
        }
        while (expression[index] != '/')
            numerator = 10 * numerator + (expression[index++] - '0');
        numerator *= numeratorSign;
        // read '/'
        ++index;
        // read denominator
        denominator = 0;
        while (index < expression.size() && std::isdigit(expression[index]))
            denominator = 10 * denominator + (expression[index++] - '0');
    }

    int calcGCD(int numerator, int denominator) const
    {
        int a = std::abs(numerator);
        int b = std::abs(denominator);
        if (a < b)
            std::swap(a, b);
        while (a % b != 0)
        {
            const int rest = a % b;
            a = b;
            b = rest;
        }
        return b;
    }
};

}

namespace FractionAdditionSubtractionTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("0/1", solution.fractionAddition("-1/2+1/2"));
    ASSERT_EQ("1/3", solution.fractionAddition("-1/2+1/2+1/3"));
    ASSERT_EQ("-1/6", solution.fractionAddition("1/3-1/2"));
    ASSERT_EQ("2/1", solution.fractionAddition("5/3+1/3"));
}

TEST(TwoSumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("41/12", solution.fractionAddition("7/2+2/3-3/4"));
}

}