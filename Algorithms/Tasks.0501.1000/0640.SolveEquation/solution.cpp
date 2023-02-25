#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string solveEquation(std::string const &equation) const
    {
        int leftSideValue = 0;
        int rightSideValue = 0;
        const size_t equalPos = equation.find('=', 0);
        processSide(equation, 0, equalPos, 1, -1, leftSideValue, rightSideValue);
        processSide(equation, equalPos + 1, equation.size(), -1, 1, leftSideValue, rightSideValue);
        if (leftSideValue == 0)
            return rightSideValue == 0 ? "Infinite solutions" : "No solution";
        return "x=" + std::to_string(rightSideValue / leftSideValue);
    }

private:
    void processSide(std::string const &equation, size_t from, size_t to, int leftSideSign, int rightSideSign, int &leftSideValue, int &rightSideValue) const
    {
        size_t position = from;
        processTerm(readTerm(equation, position, to), 1, leftSideSign, rightSideSign, leftSideValue, rightSideValue);
        while (position < to)
        {
            const char op = equation[position++];
            processTerm(readTerm(equation, position, to), op == '+' ? 1 : -1, leftSideSign, rightSideSign, leftSideValue, rightSideValue);
        }
    }

    std::string readTerm(std::string const &equation, size_t &position, size_t to) const
    {
        const size_t from = position++;
        while (position < to && equation[position] != '+' && equation[position] != '-')
            ++position;
        return equation.substr(from, position - from);
    }

    void processTerm(std::string const &term, int sign, int leftSideSign, int rightSideSign, int &leftSideValue, int &rightSideValue) const
    {
        if (term.back() == 'x')
        {
            int value = 0;
            if (term.size() == 1)
                value = 1;
            else if ((term.size() == 2) && (term[0] == '-'))
                value = -1;
            else
                value = term.size() == 1 ? 1 : std::stoi(term);
            leftSideValue += sign * leftSideSign * value;
        }
        else
            rightSideValue += sign * rightSideSign * std::stoi(term);
    }
};

}

namespace SolveEquationTask
{

TEST(SolveEquationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("x=2", solution.solveEquation("x+5-3+x=6+x-2"));
    ASSERT_EQ("Infinite solutions", solution.solveEquation("x=x"));
    ASSERT_EQ("x=0", solution.solveEquation("2x=x"));
    ASSERT_EQ("x=-1", solution.solveEquation("2x+3x-6x=x+2"));
    ASSERT_EQ("No solution", solution.solveEquation("x=x+2"));
}

TEST(SolveEquationTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("x=1", solution.solveEquation("-x=-1"));
}

}