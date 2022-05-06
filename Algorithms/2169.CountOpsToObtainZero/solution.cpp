#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countOperations(int num1, int num2) const
    {
        if (num1 < num2)
            std::swap(num1, num2);
        size_t count = 0;
        while (num2 > 0)
        {
            count += (num1 / num2);
            num1 %= num2;
            std::swap(num1, num2);
        }
        return static_cast<int>(count);
    }
};

}

namespace CountOpsToObtainZeroTask
{

TEST(CountOpsToObtainZeroTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.countOperations(2, 3));
    ASSERT_EQ(1, solution.countOperations(10, 10));
}

}