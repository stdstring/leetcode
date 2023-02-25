#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> sumZero(int n) const
    {
        std::vector<int> dest;
        dest.reserve(n);
        if (n % 2 == 1)
            dest.push_back(0);
        for (int number = 1; number <= n / 2; ++number)
        {
            dest.push_back(number);
            dest.push_back(-number);
        }
        return dest;
    }
};

}

namespace FindNUniqueIntSumUpToZeroTask
{

TEST(FindNUniqueIntSumUpToZeroTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, -1, 2, -2}), solution.sumZero(5));
    ASSERT_EQ(std::vector<int>({0, 1, -1}), solution.sumZero(3));
    ASSERT_EQ(std::vector<int>({0}), solution.sumZero(1));
}

}