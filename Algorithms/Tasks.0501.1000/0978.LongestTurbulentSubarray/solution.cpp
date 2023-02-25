#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

int sign(int value)
{
    if (value == 0)
        return 0;
    return value > 0 ? 1 : -1;
}

class Solution
{
public:
    int maxTurbulenceSize(std::vector<int> const &arr) const
    {
        size_t sizeValue = 1;
        size_t start = 0;
        for (size_t index = 1; index < arr.size(); ++index)
        {
            if (arr[index] == arr[index - 1])
                start = index;
            else if ((index == arr.size() - 1) || (sign(arr[index] - arr[index - 1]) * sign(arr[index + 1] - arr[index]) != -1))
            {
                sizeValue = std::max(sizeValue, index - start + 1);
                start = index;
            }
        }
        return static_cast<int>(sizeValue);
    }
};

}

namespace LongestTurbulentSubarrayTask
{

TEST(LongestTurbulentSubarrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.maxTurbulenceSize({9, 4, 2, 10, 7, 8, 8, 1, 9}));
    ASSERT_EQ(2, solution.maxTurbulenceSize({4, 8, 12, 16}));
    ASSERT_EQ(1, solution.maxTurbulenceSize({100}));
}

}