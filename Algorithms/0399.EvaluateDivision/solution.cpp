#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Equation
{
    Equation(std::string const &numerator, std::string const &denominator, double value) : Numerator(numerator), Denominator(denominator), Value(value)
    {
    }

    std::string Numerator;
    std::string Denominator;
    double Value;
};

class Solution
{
public:
    [[nodiscard]] std::vector<double> calcEquation(std::vector<std::vector<std::string>> const &equations, std::vector<double> const &values, std::vector<std::vector<std::string>> const &queries) const
    {
        std::unordered_map<std::string, std::unordered_map<std::string, Equation>> equationGraph;
        for (size_t index = 0; index < equations.size(); ++index)
        {
            Equation directEquation(equations[index][0], equations[index][1], values[index]);
            Equation reverseEquation(equations[index][1], equations[index][0], 1.0 / values[index]);
            equationGraph[equations[index][0]].emplace(equations[index][1], directEquation);
            equationGraph[equations[index][1]].emplace(equations[index][0], reverseEquation);
        }
        std::vector<double> result;
        result.reserve(queries.size());
        for (std::vector<std::string> const &query : queries)
            result.push_back(solveQuery(equationGraph, query[0], query[1]));
        return result;
    }

private:
    [[nodiscard]] double solveQuery(std::unordered_map<std::string, std::unordered_map<std::string, Equation>> const &equationGraph, std::string const &numerator, std::string const &denominator) const
    {
        if ((equationGraph.count(numerator) == 0) || (equationGraph.count(denominator) == 0))
            return -1.0;
        std::queue<std::vector<std::string>> paths;
        paths.push(std::vector<std::string>({numerator}));
        while (!paths.empty())
        {
            std::vector<std::string> const &current(paths.front());
            if (current.back() == denominator)
                break;
            for (auto const &entry : equationGraph.at(current.back()))
            {
                std::string const &next(entry.second.Denominator);
                if (std::find(current.cbegin(), current.cend(), next) == current.cend())
                {
                    paths.push(current);
                    paths.back().push_back(next);
                }
            }
            paths.pop();
        }
        if (paths.empty())
            return -1.0;
        double result = 1.0;
        for (size_t index = 1; index < paths.front().size(); ++index)
        {
            std::string currentNumerator(paths.front()[index - 1]);
            std::string currentDenominator(paths.front()[index]);
            const Equation equation(equationGraph.at(currentNumerator).at(currentDenominator));
            result *= equation.Value;
        }
        return result;
    }
};

}

namespace
{

void checkCalcEquation(std::vector<std::vector<std::string>> const &equations, std::vector<double> const &values, std::vector<std::vector<std::string>> const &queries, std::vector<double> const &expected)
{
    const Solution solution;
    const std::vector<double> actual(solution.calcEquation(equations, values, queries));
    ASSERT_EQ(expected.size(), actual.size());
    for (size_t index = 0; index < actual.size(); ++index)
        ASSERT_DOUBLE_EQ(expected[index], actual[index]);
}

}

namespace EvaluateDivisionTask
{

TEST(EvaluateDivisionTaskTests, Examples)
{
    checkCalcEquation({{"a", "b"}, {"b", "c"}}, {2.0, 3.0}, {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}}, {6.0, 0.5, -1.0, 1.0, -1.0});
    checkCalcEquation({{"a", "b"}, {"b", "c"}, {"bc", "cd"}}, {1.5, 2.5, 5.0}, {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}}, {3.75, 0.4, 5.0, 0.2});
    checkCalcEquation({{"a", "b"}}, {0.5}, {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}}, {0.5, 2.0, -1.0, -1.0});
}

}