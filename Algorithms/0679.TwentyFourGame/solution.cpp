#include <numeric>
#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

namespace
{

enum class Operator { Add = 1, Sub = 2, Mult = 3, Div = 4 };

class Solution
{
public:
    [[nodiscard]] bool judgePoint24(std::vector<int> const &nums) const
    {
        constexpr int expectedNumber = 24;
        const std::vector<std::vector<int>> numberCombinations({{nums[0], nums[1], nums[2], nums[3]},
                                                                {nums[0], nums[1], nums[3], nums[2]},
                                                                {nums[0], nums[2], nums[1], nums[3]},
                                                                {nums[0], nums[3], nums[1], nums[2]},
                                                                {nums[0], nums[2], nums[3], nums[1]},
                                                                {nums[0], nums[3], nums[2], nums[1]},
                                                                {nums[1], nums[0], nums[2], nums[3]},
                                                                {nums[1], nums[0], nums[3], nums[2]},
                                                                {nums[2], nums[0], nums[1], nums[3]},
                                                                {nums[3], nums[0], nums[1], nums[2]},
                                                                {nums[2], nums[0], nums[3], nums[1]},
                                                                {nums[3], nums[0], nums[2], nums[1]},
                                                                {nums[1], nums[2], nums[0], nums[3]},
                                                                {nums[1], nums[3], nums[0], nums[2]},
                                                                {nums[2], nums[1], nums[0], nums[3]},
                                                                {nums[3], nums[1], nums[0], nums[2]},
                                                                {nums[2], nums[3], nums[0], nums[1]},
                                                                {nums[3], nums[2], nums[0], nums[1]},
                                                                {nums[1], nums[2], nums[3], nums[0]},
                                                                {nums[1], nums[3], nums[2], nums[0]},
                                                                {nums[2], nums[1], nums[3], nums[0]},
                                                                {nums[3], nums[1], nums[2], nums[0]},
                                                                {nums[2], nums[3], nums[1], nums[0]},
                                                                {nums[3], nums[2], nums[1], nums[0]}});
        const std::vector<Operator> ops({Operator::Add, Operator::Sub, Operator::Mult, Operator::Div});
        const size_t opCombinationSize = ops.size() * ops.size() * ops.size();
        for (size_t combination = 0; combination < opCombinationSize; ++combination)
        {
            const Operator op1 = ops[combination % 4];
            const Operator op2 = ops[(combination / 4) % 4];
            const Operator op3 = ops[combination / 16];
            if (checkOperators(numberCombinations, op1, op2, op3, expectedNumber))
                return true;
        }
        return false;
    }

private:
    [[nodiscard]] bool checkOperators(std::vector<std::vector<int>> const &numberCombinations, Operator op1, Operator op2, Operator op3, int expectedNumber) const
    {
        for (std::vector<int> const &nums : numberCombinations)
        {
            // process a op1 b op2 c op3 d
            if (checkResult(calcExpression(nums[0], nums[1], nums[2], nums[3], op1, op2, op3), expectedNumber))
                return true;
            // process (a op1 b) op2 c op3 d
            if (checkResult(calcExpression(calcExpression(nums[0], nums[1], op1), nums[2], nums[3], op2, op3), expectedNumber))
                return true;
            // process a op1 (b op2 c) op3 d
            if (checkResult(calcExpression(nums[0], calcExpression(nums[1], nums[2], op2), nums[3], op1, op3), expectedNumber))
                return true;
            // process a op1 b op2 (c op3 d)
            if (checkResult(calcExpression(nums[0], nums[1], calcExpression(nums[2], nums[3], op3), op2, op3), expectedNumber))
                return true;
            // process (a op1 b) op2 (c op3 d)
            if (checkResult(calcExpression(calcExpression(nums[0], nums[1], op1), calcExpression(nums[2], nums[3], op3), op2), expectedNumber))
                return true;
            // process (a op1 b op2 c) op3 d
            if (checkResult(calcExpression(calcExpression(nums[0], nums[1], nums[2], op1, op2), nums[3], op3), expectedNumber))
                return true;
            // process a op1 (b op2 c op3 d)
            if (checkResult(calcExpression(nums[0], calcExpression(nums[1], nums[2], nums[3], op2, op3), op1), expectedNumber))
                return true;
        }
        return false;
    }

    [[nodiscard]] bool checkResult(std::pair<int, int> result, int expectedNumber) const
    {
        if (result.second == 0)
            return false;
        result = simplify(result);
        return (result.first == expectedNumber) && (result.second == 1);
    }

    [[nodiscard]] std::pair<int, int> calcExpression(int a, int b, Operator op) const
    {
        return calcExpression({a, 1}, {b, 1}, op);
    }

    [[nodiscard]] std::pair<int, int> calcExpression(std::pair<int, int> a, int b, Operator op) const
    {
        return calcExpression(a, {b, 1}, op);
    }

    [[nodiscard]] std::pair<int, int> calcExpression(int a, std::pair<int, int> b, Operator op) const
    {
        return calcExpression({a, 1}, b, op);
    }

    [[nodiscard]] std::pair<int, int> calcExpression(std::pair<int, int> a, std::pair<int, int> b, Operator op) const
    {
        switch (op)
        {
            case Operator::Add:
                return {a.first * b.second + b.first * a.second, a.second * b.second};
            case Operator::Sub:
                return {a.first * b.second - b.first * a.second, a.second * b.second};
            case Operator::Mult:
                return {a.first *  b.first, a.second * b.second};
            case Operator::Div:
                return {a.first * b.second, a.second * b.first};
        }
        throw std::logic_error("bad execution case");
    }

    [[nodiscard]] std::pair<int, int> calcExpression(int a, int b, int c, Operator op1, Operator op2) const
    {
        return calcExpression({a, 1}, {b, 1}, {c, 1}, op1, op2);
    }

    [[nodiscard]] std::pair<int, int> calcExpression(std::pair<int, int> a, int b, int c, Operator op1, Operator op2) const 
    {
        return calcExpression(a, {b, 1}, {c, 1}, op1, op2);
    }

    [[nodiscard]] std::pair<int, int> calcExpression(int a, std::pair<int, int> b, int c, Operator op1, Operator op2) const
    {
        return calcExpression({a, 1}, b, {c, 1}, op1, op2);
    }

    [[nodiscard]] std::pair<int, int> calcExpression(int a, int b, std::pair<int, int> c, Operator op1, Operator op2) const
    {
        return calcExpression({a, 1}, {b, 1}, c, op1, op2);
    }

    [[nodiscard]] std::pair<int, int> calcExpression(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c, Operator op1, Operator op2) const
    {
        if (op1 >= op2)
            return calcExpression(calcExpression(a, b, op1), c, op2);
        return calcExpression(a, calcExpression(b, c, op2), op1);
    }

    [[nodiscard]] std::pair<int, int> calcExpression(int a, int b, int c, int d, Operator op1, Operator op2, Operator op3) const
    {
        const std::pair<int, int> aValue({a, 1});
        const std::pair<int, int> bValue({b, 1});
        const std::pair<int, int> cValue({c, 1});
        const std::pair<int, int> dValue({d, 1});
        if ((op1 >= op2) && (op1 >= op3))
            return calcExpression(calcExpression(aValue, bValue, op1), cValue, dValue, op2, op3);
        if ((op2 >= op1) && (op2 >= op3))
            return calcExpression(aValue, calcExpression(bValue, cValue, op2), dValue, op1, op3);
        // (op3 >= op1) && (op3 >= op2)
        return calcExpression(aValue, bValue, calcExpression(cValue, dValue, op3), op1, op2);
    }

    [[nodiscard]] std::pair<int, int> simplify(std::pair<int, int> n) const
    {
        const int gcd = std::gcd(n.first, n.second);
        return {n.first / gcd, n.second / gcd};
    }
};

}

namespace TwentyFourGameTask
{

TEST(TwentyFourGameTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.judgePoint24({4, 1, 8, 7}));
    ASSERT_EQ(false, solution.judgePoint24({1, 2, 1, 2}));
}

}
