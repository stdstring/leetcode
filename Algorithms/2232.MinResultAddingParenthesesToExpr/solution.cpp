#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string minimizeResult(std::string const &expression) const
    {
        const size_t sumOpPos = expression.find('+');
        int bestResult = INT_MAX;
        std::pair<size_t, size_t> bestParenthesesPos(0, expression.size());
        for (size_t openBracePos = 0; openBracePos <= sumOpPos - 1; ++openBracePos)
        {
            const int leftFactor = (openBracePos == 0) ? 1 : stoi(expression.substr(0, openBracePos));
            const int leftTerm = stoi(expression.substr(openBracePos, sumOpPos - openBracePos));
            for (size_t closeBracePos = sumOpPos + 2; closeBracePos <= expression.size(); ++closeBracePos)
            {
                const int rightTerm = stoi(expression.substr(sumOpPos + 1, closeBracePos - sumOpPos - 1));
                const int rightFactor = closeBracePos == expression.size() ? 1 : stoi(expression.substr(closeBracePos));
                const int currentResult = leftFactor * (leftTerm + rightTerm) * rightFactor;
                if (currentResult < bestResult)
                {
                    bestResult = currentResult;
                    bestParenthesesPos = {openBracePos, closeBracePos};
                }
            }
        }
        std::string result(expression);
        result.insert(bestParenthesesPos.second, ")");
        result.insert(bestParenthesesPos.first, "(");
        return result;
    }
};

}

namespace MinResultAddingParenthesesToExprTask
{

TEST(MinResultAddingParenthesesToExprTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("2(47+38)", solution.minimizeResult("247+38"));
    ASSERT_EQ("1(2+3)4", solution.minimizeResult("12+34"));
    ASSERT_EQ("(999+999)", solution.minimizeResult("999+999"));
}

}