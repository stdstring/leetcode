#include <string>
#include <tuple>

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
        return static_cast<int>(std::get<0>(processExpression(source, 0)));
    }

private:
    std::tuple<long long, size_t> processExpression(std::string const &source, size_t pos) const
    {
        pos = skipWhitespaces(source, pos);
        long long result = 0;
        bool hasValue = false;
        while (pos < source.size() && source[pos] != ')')
        {
            if (!hasValue)
            {
                std::tie(result, pos) = source[pos] == '(' ? processExpression(source, pos + 1) : readNumber(source, pos);
                hasValue = true;
                continue;
            }
            Operator op;
            std::tie(op, pos) = readOp(source, pos++);
            long long secondOperand;
            std::tie(secondOperand, pos) = source[pos] == '(' ? processExpression(source, pos + 1) : readNumber(source, pos);
            result = processOp(result, op, secondOperand);
        }
        return std::make_tuple(result, pos < source.size() ? skipWhitespaces(source, pos + 1) : pos);
    }

    size_t skipWhitespaces(std::string const &source, size_t pos) const
    {
        while (pos < source.size() && source[pos] == ' ')
            ++pos;
        return pos;
    }

    std::tuple<long long, size_t> readNumber(std::string const &source, size_t pos) const
    {
        long long result = 0;
        while (pos < source.size() && '0' <= source[pos] && source[pos] <= '9')
        {
            result = 10 * result + (source[pos] - '0');
            ++pos;
        }
        return std::make_tuple(result, skipWhitespaces(source, pos));
    }

    std::tuple<Operator, size_t> readOp(std::string const &source, size_t pos) const
    {
        switch (source[pos])
        {
            case '+':
                return std::make_tuple(Operator::ADD, skipWhitespaces(source, pos + 1));
            case '-':
                return std::make_tuple(Operator::SUB, skipWhitespaces(source, pos + 1));
            default:
                return std::make_tuple(Operator::NONE, pos + 1);
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