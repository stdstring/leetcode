#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> diffWaysToCompute(std::string const &expression) const
    {
        std::vector<int> parts(splitExpression(expression));
        std::vector<int> result(diffWaysToCompute(parts, 0, parts.size()));
        std::ranges::sort(result);
        return result;
    }

private:
    static constexpr int AddOp = 1000;
    static constexpr int SubOp = 1001;
    static constexpr int MultOp = 1002;

    [[nodiscard]] std::vector<int> splitExpression(std::string const &expression) const
    {
        std::vector<int> result;
        int currentNumber = 0;
        for (const char ch : expression)
        {
            switch (ch)
            {
            case '+':
                result.emplace_back(currentNumber);
                currentNumber = 0;
                result.emplace_back(AddOp);
                break;
            case '-':
                result.emplace_back(currentNumber);
                currentNumber = 0;
                result.emplace_back(SubOp);
                break;
            case '*':
                result.emplace_back(currentNumber);
                currentNumber = 0;
                result.emplace_back(MultOp);
                break;
            default:
                currentNumber = 10 * currentNumber + (ch - '0');
                break;
            }
        }
        result.emplace_back(currentNumber);
        return result;
    }

    [[nodiscard]] std::vector<int> diffWaysToCompute(std::vector<int> const &expression, size_t start, size_t size) const
    {
        if (size == 1)
            return {expression[start]};
        std::vector<int> result;
        for (size_t shift = 0; shift < size; ++shift)
        {
            switch (int current = expression[start + shift])
            {
            case AddOp:
            case SubOp:
            case MultOp:
            {
                std::vector<int> left(diffWaysToCompute(expression, start, shift));
                std::vector<int> right(diffWaysToCompute(expression, start + shift + 1, size - shift - 1));
                combineSubExpressions(left, current, right, result);
                break;
            }
            default:
                // do nothing
                break;
            }
        }
        return result;
    }

    void combineSubExpressions(std::vector<int> const &left, int op, std::vector<int> const &right, std::vector<int> &dest) const
    {
        for (int leftPart : left)
        {
            for (int rightPart : right)
            {
                switch (op)
                {
                case AddOp:
                    dest.emplace_back(leftPart + rightPart);
                    break;
                case SubOp:
                    dest.emplace_back(leftPart - rightPart);
                    break;
                case MultOp:
                    dest.emplace_back(leftPart * rightPart);
                    break;
                default:
                    throw std::logic_error("Unexpected branch");
                }
            }
        }
    }
};

}

namespace DifferentWaysAddParenthesesTask
{

TEST(DifferentWaysAddParenthesesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 2}), solution.diffWaysToCompute("2-1-1"));
    ASSERT_EQ(std::vector<int>({-34, -14, -10, -10, 10}), solution.diffWaysToCompute("2*3-4*5"));
}

}