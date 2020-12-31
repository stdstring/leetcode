#include <string>

#include "gtest/gtest.h"

namespace
{

enum Operator
{
    NONE, ADD, SUB
};

class Solution
{
public:
    int calculate(std::string const &source) const
    {
        size_t pos = 0;
        return static_cast<int>(processExpression(source, pos));
    }

private:
    long long processExpression(std::string const &source, size_t &pos) const
    {
        skipWhitespaces(source, pos);
        long long result = 0;
        bool hasValue = false;
        while (pos < source.size() && source[pos] != ')')
        {
            if (!hasValue)
            {
                result = source[pos] == '(' ? processExpression(source, ++pos) : readNumber(source, pos);
                // for processing such cases: "(  3   )"
                skipWhitespaces(source, pos);
                hasValue = true;
                continue;
            }
            skipWhitespaces(source, pos);
            // operator
            const Operator op = readOp(source, pos);
            skipWhitespaces(source, pos);
            // right operand
            const long long secondOperand = source[pos] == '(' ? processExpression(source, ++pos) : readNumber(source, pos);
            result = processOp(result, op, secondOperand);
            skipWhitespaces(source, pos);
        }
        if (pos < source.size() && source[pos] == ')')
            ++pos;
        return result;
    }

    void skipWhitespaces(std::string const &source, size_t &pos) const
    {
        while (pos < source.size() && source[pos] == ' ')
            ++pos;
    }

    long long readNumber(std::string const &source, size_t &pos) const
    {
        long long result = 0;
        while (pos < source.size() && '0' <= source[pos] && source[pos] <= '9')
            result = 10 * result + (source[pos++] - '0');
        return result;
    }

    Operator readOp(std::string const &source, size_t &pos) const
    {
        switch (source[pos++])
        {
        case '+':
            return Operator::ADD;
        case '-':
            return Operator::SUB;
        default:
            return Operator::NONE;
        }
    }

    long long processOp(long long firstOperand, Operator op, long long secondOperand) const
    {
        switch (op)
        {
            case Operator::ADD:
                return firstOperand + secondOperand;
            case Operator::SUB:
                return firstOperand - secondOperand;
            default:
                return 0;
        }
    }
};

}

namespace BasicCalculatorTask
{

TEST(BasicCalculatorTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.calculate("1 + 1"));
    ASSERT_EQ(3, solution.calculate(" 2-1 + 2 "));
    ASSERT_EQ(23, solution.calculate("(1+(4+5+2)-3)+(6+8)"));
}

TEST(BasicCalculatorTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(3, solution.calculate("   (  3 ) "));
}

}