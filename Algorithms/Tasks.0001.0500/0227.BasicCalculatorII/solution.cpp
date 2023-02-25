#include <string>
#include <tuple>

#include "gtest/gtest.h"

namespace
{

enum Operator
{
    NONE, ADD, SUB, MUL, DIV
};

struct State
{
    State() : firstOperand(0), op(Operator::NONE), secondOperand(1), operandCount(0)
    {
    }

    long long firstOperand;
    Operator op;
    long long secondOperand;
    size_t operandCount;
};

class Solution
{
public:
    int calculate(std::string const &source) const
    {
        size_t pos = 0;
        skipWhitespaces(source, pos);
        State state;
        while (pos < source.size())
        {
            if (state.operandCount == 0)
            {
                state.firstOperand = readNumber(source, pos);
                state.operandCount = 1;
                // for processing such cases: "5   "
                skipWhitespaces(source, pos);
                continue;
            }
            skipWhitespaces(source, pos);
            // operator
            const Operator op = readOp(source, pos);
            skipWhitespaces(source, pos);
            // right operand
            const long long number = readNumber(source, pos);
            skipWhitespaces(source, pos);
            // process
            if (state.operandCount == 1)
            {
                if (op == Operator::MUL || op == Operator::DIV)
                    state.firstOperand = processOp(state.firstOperand, op, number);
                else
                {
                    state.op = op;
                    state.secondOperand = number;
                    state.operandCount = 2;
                }
            }
            else
            {
                if (op == Operator::MUL || op == Operator::DIV)
                    state.secondOperand = processOp(state.secondOperand, op, number);
                else
                {
                    state.firstOperand = processOp(state);
                    state.op = op;
                    state.secondOperand = number;
                }
            }
        }
        return state.operandCount == 1 ? static_cast<int>(state.firstOperand) : static_cast<int>(processOp(state));
    }

private:
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
        case '*':
            return Operator::MUL;
        case '/':
            return Operator::DIV;
        default:
            return Operator::NONE;
        }
    }

    long long processOp(State const &state) const
    {
        return processOp(state.firstOperand, state.op, state.secondOperand);
    }

    long long processOp(long long firstOperand, Operator op, long long secondOperand) const
    {
        switch (op)
        {
            case Operator::ADD:
                return firstOperand + secondOperand;
            case Operator::SUB:
                return firstOperand - secondOperand;
            case Operator::MUL:
                return firstOperand * secondOperand;
            case Operator::DIV:
                return firstOperand / secondOperand;
            default:
                return 0;
        }
    }
};

}

namespace BasicCalculatorIITask
{

TEST(BasicCalculatorIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(7, solution.calculate("3+2*2"));
    ASSERT_EQ(1, solution.calculate(" 3/2 "));
    ASSERT_EQ(5, solution.calculate(" 3+5 / 2 "));
}

TEST(BasicCalculatorIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(1, solution.calculate("1"));
    ASSERT_EQ(5, solution.calculate("5   "));
}

}