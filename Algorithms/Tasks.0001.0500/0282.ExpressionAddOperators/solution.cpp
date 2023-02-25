#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct CalculationState
{
    CalculationState() : OperandCount(0), Operand1(0), Operation1(0), Operand2(0), Operation2(0)
    {
    }

    int OperandCount;
    long long Operand1;
    int Operation1;
    long long Operand2;
    int Operation2;
};

class Solution
{
public:
    std::vector<std::string> addOperators(std::string const &num, int target) const
    {
        if (num.empty())
            return {};
        std::vector<uint8_t> digits;
        digits.reserve(num.size());
        for (char digit : num)
            digits.push_back(digit - '0');
        const int maxOperation = (1 << (2 * num.size() - 2)) - 1;
        std::vector<int> suitableOperations;
        for (int operation = 0; operation <= maxOperation; ++operation)
        {
            if (checkOperationsValue(digits, operation, target))
                suitableOperations.push_back(operation);
        }
        std::vector<std::string> dest;
        dest.reserve(suitableOperations.size());
        for (int operation : suitableOperations)
            dest.push_back(createExpression(num, operation));
        return dest;
    }

private:
    // operations: 00 - empty, 01 - '+', 10 - '-', 11 - '*'
    constexpr static int OperationMask = 0b11;
    constexpr static int EmptyOp = 0b00;
    constexpr static int AddOp = 0b01;
    constexpr static int SubOp = 0b10;
    constexpr static int MultOp = 0b11;

    void updateState(CalculationState &state, long long operand, int operation) const
    {
        if (state.OperandCount == 0)
        {
            state.Operand1 = operand;
            state.Operation1 = operation;
            state.OperandCount = 1;
        }
        else if (state.OperandCount == 1)
        {
            if (state.Operation1 == MultOp)
            {
                state.Operand1 *= operand;
                state.Operation1 = operation;
            }
            else
            {
                state.Operand2 = operand;
                state.Operation2 = operation;
                state.OperandCount = 2;
            }
        }
        else
        {
            if (state.Operation2 == MultOp)
            {
                state.Operand2 *= operand;
                state.Operation2 = operation;
            }
            else
            {
                state.Operand1 = calcValue(state.Operand1, state.Operation1, state.Operand2);
                state.Operation1 = state.Operation2;
                state.Operand2 = operand;
                state.Operation2 = operation;
            }
        }
    }

    long long calcValue(long long operand1, int operation, long long operand2) const
    {
        switch(operation)
        {
            case AddOp:
                return operand1 + operand2;
            case SubOp:
                return operand1 - operand2;
            case MultOp:
                return operand1 * operand2;
            default:
                return 0;
        }
    }

    long long calcValue(CalculationState &state, long long operand) const
    {
        if (state.OperandCount == 0)
            return operand;
        if (state.OperandCount == 1)
            return calcValue(state.Operand1, state.Operation1, operand);
        if (state.Operation2 == MultOp)
            return calcValue(state.Operand1, state.Operation1, calcValue(state.Operand2, state.Operation2, operand));
        return calcValue(calcValue(state.Operand1, state.Operation1, state.Operand2), state.Operation2, operand);
    }

    bool checkOperationsValue(std::vector<uint8_t> const &digits, int operations, int target) const
    {
        CalculationState state;
        long long currentOperand = 0;
        size_t nextPos = 0;
        while (operations > 0)
        {
            currentOperand = 10 * currentOperand + digits[nextPos++];
            const int operation = operations & OperationMask;
            if (operation == EmptyOp && currentOperand == 0)
                return false;
            if (operation != EmptyOp)
            {
                updateState(state, currentOperand, operation);
                currentOperand = 0;
            }
            operations >>= 2;
        }
        if ((nextPos + 1) < digits.size() && digits[nextPos] == 0)
            return false;
        while (nextPos < digits.size())
            currentOperand = 10 * currentOperand + digits[nextPos++];
        return calcValue(state, currentOperand) == target;
    }

    std::string createExpression(std::string const &num, int operations) const
    {
        std::string expression;
        expression.push_back(num[0]);
        size_t nextPos = 1;
        while (operations > 0)
        {
            switch (operations & OperationMask)
            {
                case AddOp:
                    expression.push_back('+');
                    break;
                case SubOp:
                    expression.push_back('-');
                    break;
                case MultOp:
                    expression.push_back('*');
                    break;
                default:
                    /* do nothing */;
            }
            expression.push_back(num[nextPos++]);
            operations >>= 2;
        }
        expression.append(num, nextPos);
        return expression;
    }
};

}

namespace ExpressionAddOperatorsTask
{

TEST(ExpressionAddOperatorsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"1+2+3", "1*2*3"}), solution.addOperators("123", 6));
    ASSERT_EQ(std::vector<std::string>({"2*3+2", "2+3*2"}), solution.addOperators("232", 8));
    ASSERT_EQ(std::vector<std::string>({"1*0+5","10-5"}), solution.addOperators("105", 5));
    ASSERT_EQ(std::vector<std::string>({"0+0", "0-0", "0*0"}), solution.addOperators("00", 0));
    ASSERT_EQ(std::vector<std::string>(), solution.addOperators("3456237490", 9191));
}

TEST(ExpressionAddOperatorsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>(), solution.addOperators("", 5));
}

}