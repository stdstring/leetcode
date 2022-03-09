#include <functional>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class CustomFunction
{
public:
    CustomFunction(std::function<int(int, int)> const &hiddenFunc) : _hiddenFunc(hiddenFunc)
    {
    }

    int f(int x, int y)
    {
        return _hiddenFunc(x, y);
    }

private:
    std::function<int(int, int)> _hiddenFunc;
};

}

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> findSolution(CustomFunction &customfunction, int z) const
    {
        constexpr int minValue = 1;
        constexpr int maxValue = 1000;
        std::vector<std::vector<int>> dest;
        for (int x = minValue; (x <= maxValue) && customfunction.f(x, minValue) <= z; ++x)
        {
            if (customfunction.f(x, maxValue) < z)
                continue;
            int yLeft = minValue;
            int yRight = maxValue;
            while (yLeft < yRight)
            {
                const int yMiddle = (yRight + yLeft) / 2;
                const int value = customfunction.f(x, yMiddle);
                if (value == z)
                    yLeft = yRight = yMiddle;
                if (value < z)
                    yLeft = yMiddle + 1;
                if (value > z)
                    yRight = yMiddle - 1;
            }
            if (customfunction.f(x, yLeft) == z)
                dest.push_back({x, yLeft});
        }
        return dest;
    }
};

}

namespace
{

void checkFindSolution(std::function<int(int, int)> const &hiddenFunc, int z, std::vector<std::vector<int>> const &expected)
{
    CustomFunction customFunction(hiddenFunc);
    const Solution solution;
    ASSERT_EQ(expected, solution.findSolution(customFunction, z));
}

}

namespace FindPositiveIntSolutionForGivenEquationTask
{

TEST(FindPositiveIntSolutionForGivenEquationTaskTests, Examples)
{
    checkFindSolution([](int x, int y) { return x + y; }, 5, {{1, 4}, {2, 3}, {3, 2}, {4, 1}});
    checkFindSolution([](int x, int y) { return x * y; }, 5, {{1, 5}, {5, 1}});
}

}