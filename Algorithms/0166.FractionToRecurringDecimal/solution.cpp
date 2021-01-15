#include <cstdlib>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string fractionToDecimal(int numerator, int denominator) const
    {
        return fractionToDecimalImpl(numerator, denominator);
    }

private:
    std::string fractionToDecimalImpl(long long numerator, long long denominator) const
    {
        std::string result;
        if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator > 0))
            result.push_back('-');
        numerator = std::abs(numerator);
        denominator = std::abs(denominator);
        const long long integerPart = numerator / denominator;
        result.append(std::to_string(integerPart));
        if (numerator % denominator == 0)
            return result;
        result.push_back('.');
        processFraction(numerator, denominator, result);
        return result;
    }

    void processFraction(long long numerator, long long denominator, std::string &result) const
    {
        std::unordered_map<long long, size_t> knownReminderPos;
        numerator = 10 * (numerator % denominator);
        bool continueProcess = true;
        while (continueProcess)
        {
            const long long number = numerator / denominator;
            const long long reminder = numerator % denominator;
            if (reminder == 0)
                continueProcess = false;
            std::unordered_map<long long, size_t>::const_iterator reminderPos = knownReminderPos.find(numerator);
            if (reminderPos == knownReminderPos.cend())
            {
                knownReminderPos[numerator] = result.size();
                result.append(std::to_string(number));
                numerator = 10 * reminder;
            }
            else
            {
                result.insert(reminderPos->second, 1, '(');
                result.push_back(')');
                continueProcess = false;
            }
        }
    }
};

}

namespace FractionToRecurringDecimalTask
{

TEST(FractionToRecurringDecimalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("0.5", solution.fractionToDecimal(1, 2));
    ASSERT_EQ("2", solution.fractionToDecimal(2, 1));
    ASSERT_EQ("0.(6)", solution.fractionToDecimal(2, 3));
    ASSERT_EQ("0.(012)", solution.fractionToDecimal(4, 333));
    ASSERT_EQ("0.2", solution.fractionToDecimal(1, 5));
}

TEST(FractionToRecurringDecimalTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("-2147483648", solution.fractionToDecimal(INT_MIN, 1));
    ASSERT_EQ("0.0000000004656612873077392578125", solution.fractionToDecimal(-1, INT_MIN));
}

}