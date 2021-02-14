#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool parseBoolExpr(std::string const &expression) const
    {
        size_t index = 0;
        return evaluateExpr(expression, index, {});
    }

private:
    bool evaluateExpr(std::string const &expression, size_t &index, std::vector<char> const &followChars) const
    {
        bool result = false;
        while (index < expression.size() && std::count(followChars.cbegin(), followChars.cend(), expression[index]) == 0)
        {
            switch (expression[index])
            {
                case 't':
                    result = true;
                    ++index;
                    break;
                case 'f':
                    result = false;
                    ++index;
                    break;
                case '!':
                    result = evaluateNotExpr(expression, index);
                    break;
                case '&':
                    result = evaluateAndExpr(expression, index);
                    break;
                case '|':
                    result = evaluateOrExpr(expression, index);
                    break;
                default:
                    result = false;
            }
        }
        return result;
    }

    bool evaluateAndExpr(std::string const &expression, size_t &index) const
    {
        bool result = true;
        // process &(
        index += 2;
        while (expression[index] != ')')
        {
            // process ,
            if (expression[index] == ',')
                ++index;
            // process expri
            result &= evaluateExpr(expression, index, {',', ')'});
        }
        // process )
        ++index;
        return result;
    }

    bool evaluateOrExpr(std::string const &expression, size_t &index) const
    {
        bool result = false;
        // process |(
        index += 2;
        while (expression[index] != ')')
        {
            // process ,
            if (expression[index] == ',')
                ++index;
            // process expri
            result |= evaluateExpr(expression, index, {',', ')'});
        }
        // process )
        ++index;
        return result;
    }

    bool evaluateNotExpr(std::string const &expression, size_t &index) const
    {
        // process !(
        index += 2;
        const bool value = evaluateExpr(expression, index, {')'});
        // process )
        index += 1;
        return !value;
    }
};

}

namespace ParsingBooleanExpressionTask
{

TEST(ParsingBooleanExpressionTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.parseBoolExpr("!(f)"));
    ASSERT_EQ(true, solution.parseBoolExpr("|(f,t)"));
    ASSERT_EQ(false, solution.parseBoolExpr("&(t,f)"));
    ASSERT_EQ(false, solution.parseBoolExpr("|(&(t,f,t),!(t))"));
}

}