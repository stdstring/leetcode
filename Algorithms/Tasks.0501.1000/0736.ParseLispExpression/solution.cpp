#include <cctype>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int evaluate(std::string const &expression) const
    {
        size_t pos = 0;
        std::unordered_map<std::string, int> context;
        return evaluateExpr(expression, pos, context);
    }

private:
    static constexpr char ExpressionEnd = ')';
    static const std::string LetExprStart;
    static const std::string AddExprStart;
    static const std::string MultExprStart;

    int evaluateExpr(std::string const &expression, size_t &pos, std::unordered_map<std::string, int> &context) const
    {
        if (std::isdigit(expression[pos]) || expression[pos] == '-')
            return readNumber(expression, pos);
        if (std::islower(expression[pos]))
            return context[readName(expression, pos)];
        if (isLetExpr(expression, pos))
            return evaluateLetExpr(expression, pos, context);
        if (isAddExpr(expression, pos))
            return evaluateAddExpr(expression, pos, context);
        if (isMultExpr(expression, pos))
            return evaluateMultExpr(expression, pos, context);
        throw std::logic_error("bad expression");
    }

    bool isLetExpr(std::string const &expression, size_t const &pos) const
    {
        return expression.compare(pos, LetExprStart.size(), LetExprStart) == 0;
    }

    int evaluateLetExpr(std::string const &expression, size_t &pos, std::unordered_map<std::string, int> const &parentContext) const
    {
        std::unordered_map<std::string, int> currentContext(parentContext);
        // process leading '(let'
        pos += LetExprStart.size();
        // process body
        skipWhitespaces(expression, pos);
        while (evaluateAssignExpr(expression, pos, currentContext))
            skipWhitespaces(expression, pos);
        const int value = evaluateExpr(expression, pos, currentContext);
        skipWhitespaces(expression, pos);
        // process trailing ')'
        ++pos;
        return value;
    }

    bool evaluateAssignExpr(std::string const &expression, size_t &pos, std::unordered_map<std::string, int> &context) const
    {
        const size_t startPos = pos;
        if (!std::islower(expression[pos]))
            return false;
        // read variable name
        const std::string name(readName(expression, pos));
        skipWhitespaces(expression, pos);
        // read expression value
        if (expression[pos] == ExpressionEnd)
        {
            pos = startPos;
            return false;
        }
        const int value = evaluateExpr(expression, pos, context);
        context[name] = value;
        return true;
    }

    bool isAddExpr(std::string const &expression, size_t const &pos) const
    {
        return expression.compare(pos, AddExprStart.size(), AddExprStart) == 0;
    }

    int evaluateAddExpr(std::string const &expression, size_t &pos, std::unordered_map<std::string, int> &context) const
    {
        // process leading '(add'
        pos += AddExprStart.size();
        // process body
        skipWhitespaces(expression, pos);
        const int value1 = evaluateExpr(expression, pos, context);
        skipWhitespaces(expression, pos);
        const int value2 = evaluateExpr(expression, pos, context);
        skipWhitespaces(expression, pos);
        // process trailing ')'
        ++pos;
        return value1 + value2;
    }

    bool isMultExpr(std::string const &expression, size_t const &pos) const
    {
        return expression.compare(pos, MultExprStart.size(), MultExprStart) == 0;
    }

    int evaluateMultExpr(std::string const &expression, size_t &pos, std::unordered_map<std::string, int> &context) const
    {
        // process leading '(mult'
        pos += MultExprStart.size();
        // process body
        skipWhitespaces(expression, pos);
        const int value1 = evaluateExpr(expression, pos, context);
        skipWhitespaces(expression, pos);
        const int value2 = evaluateExpr(expression, pos, context);
        skipWhitespaces(expression, pos);
        // process trailing ')'
        ++pos;
        return value1 * value2;
    }

    int readNumber(std::string const &expression, size_t &pos) const
    {
        int number = 0;
        int sign = 1;
        if (expression[pos] == '-')
        {
            sign = -1;
            ++pos;
        }
        while (pos < expression.size() && std::isdigit(expression[pos]))
            number = 10 * number + (expression[pos++] - '0');
        return sign * number;
    }

    std::string readName(std::string const &expression, size_t &pos) const
    {
        std::string name;
        name.push_back(expression[pos++]);
        while (pos < expression.size() && (std::islower(expression[pos]) || std::isdigit(expression[pos])))
            name.push_back(expression[pos++]);
        return name;
    }

    void skipWhitespaces(std::string const &expression, size_t &pos) const
    {
        while (pos < expression.size() && expression[pos] == ' ')
            ++pos;
    }
};

const std::string Solution::LetExprStart = "(let";
const std::string Solution::AddExprStart = "(add";
const std::string Solution::MultExprStart = "(mult";

}

namespace ParseLispExpressionTask
{

TEST(ParseLispExpressionTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.evaluate("(add 1 2)"));
    ASSERT_EQ(15, solution.evaluate("(mult 3 (add 2 3))"));
    ASSERT_EQ(10, solution.evaluate("(let x 2 (mult x 5))"));
    ASSERT_EQ(14, solution.evaluate("(let x 2 (mult x (let x 3 y 4 (add x y))))"));
    ASSERT_EQ(2, solution.evaluate("(let x 3 x 2 x)"));
    ASSERT_EQ(5, solution.evaluate("(let x 1 y 2 x (add x y) (add x y))"));
    ASSERT_EQ(6, solution.evaluate("(let x 2 (add (let x 3 (let x 4 x)) x))"));
    ASSERT_EQ(4, solution.evaluate("(let a1 3 b2 (add a1 1) b2)"));
}

TEST(ParseLispExpressionTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(-12, solution.evaluate("(let x 7 -12)"));
}


}