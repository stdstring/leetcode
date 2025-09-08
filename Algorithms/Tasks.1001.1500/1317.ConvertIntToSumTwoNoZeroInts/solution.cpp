#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> getNoZeroIntegers(int n) const
    {
        for (int number = 1; number <= n / 2; ++number)
        {
            if (isNoZeroNumber(number) && isNoZeroNumber(n - number))
                return {number, n - number};
        }
        return {0, 0};
    }

private:
    [[nodiscard]] bool isNoZeroNumber(int number) const
    {
        for (;number > 0; number /= 10)
        {
            if ((number % 10) == 0)
                return false;
        }
        return true;
    }
};

}

namespace TwoSumTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 1}), solution.getNoZeroIntegers(2));
    ASSERT_EQ(std::vector<int>({2, 9}), solution.getNoZeroIntegers(11));
}

}