#include <stack>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int evalRPN(std::vector<std::string> const &tokens) const
    {
        std::stack<int> stack;
        for(std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
        {
            if (*it == "+" || *it == "-" || *it == "*" || *it == "/")
                processOperation(stack, *it);
            else
                stack.push(atoi(it->c_str()));
        }
        return stack.top();
    }

private:
    void processOperation(std::stack<int> &stack, std::string const &op) const
    {
        const int operand2 = stack.top();
        stack.pop();
        const int operand1 = stack.top();
        stack.pop();
        if (op == "+")
            stack.push(operand1 + operand2);
        else if (op == "-")
            stack.push(operand1 - operand2);
        else if (op == "*")
            stack.push(operand1 * operand2);
        else if (op == "/")
            stack.push(operand1 / operand2);
    }
};

}

namespace EvaluateReversePolishNotationTask
{

TEST(EvaluateReversePolishNotationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(9, solution.evalRPN({"2", "1", "+", "3", "*"}));
    ASSERT_EQ(6, solution.evalRPN({"4", "13", "5", "/", "+"}));
    ASSERT_EQ(22, solution.evalRPN({"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}));
}

}