class Solution
{
public:
    int evalRPN(std::vector<std::string> const &tokens)
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
    void processOperation(std::stack<int> &stack, std::string const &op)
    {
        int operand2 = stack.top();
        stack.pop();
        int operand1 = stack.top();
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