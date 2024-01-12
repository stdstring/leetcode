#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<int> const &nums, int k) const
    {
        const int totalValue = std::accumulate(nums.cbegin(), nums.cend(), 0, [](int acc, int number) { return acc ^ number; });
        size_t operationCount = 0;
        for (int mask = 1; (mask <= totalValue) || (mask <= k); mask <<= 1)
        {
            if ((totalValue & mask) != (k & mask))
                ++operationCount;
        }
        return static_cast<int>(operationCount);
    }
};

}

namespace MinNumberOpsMakeArrayXOREqual2KTask
{

TEST(MinNumberOpsMakeArrayXOREqual2KTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperations({2, 1, 3, 4}, 1));
    ASSERT_EQ(0, solution.minOperations({2, 0, 2, 0}, 0));
}

}