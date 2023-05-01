#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double average(std::vector<int> const &salary) const
    {
        int sum = 0;
        int minValue = INT_MAX;
        int maxValue = INT_MIN;
        for (int value : salary)
        {
            sum += value;
            minValue = std::min(minValue, value);
            maxValue = std::max(maxValue, value);
        }
        return 1.0 * (sum - minValue - maxValue) / static_cast<double>(salary.size() - 2);
    }
};

}

namespace AverageSalaryExcludingMinMaxSalaryTask
{

TEST(AverageSalaryExcludingMinMaxSalaryTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_DOUBLE_EQ(2500.0, solution.average({4000, 3000, 1000, 2000}));
    ASSERT_DOUBLE_EQ(2000.0, solution.average({1000, 2000, 3000}));
}

}