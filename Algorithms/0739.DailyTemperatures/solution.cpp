#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> dailyTemperatures(std::vector<int> const &temps) const
    {
        std::stack<size_t> temperatureIndexStack;
        std::vector<int> result(temps.size(), 0);
        for (size_t index = 0; index < temps.size(); ++index)
        {
            while (!temperatureIndexStack.empty() && (temps[temperatureIndexStack.top()] < temps[index]))
            {
                result[temperatureIndexStack.top()] = static_cast<int>(index - temperatureIndexStack.top());
                temperatureIndexStack.pop();
            }
            temperatureIndexStack.push(index);
        }
        return result;
    }
};

}

namespace DailyTemperaturesTask
{

TEST(DailyTemperaturesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 1, 4, 2, 1, 1, 0, 0}), solution.dailyTemperatures({73, 74, 75, 71, 69, 72, 76, 73}));
}

}