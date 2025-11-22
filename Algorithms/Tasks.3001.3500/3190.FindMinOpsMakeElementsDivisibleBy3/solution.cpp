#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumOperations(std::vector<int> const &nums) const
    {
        size_t operationCount = 0;
        for (const int number : nums)
            operationCount += (((number % 3) == 0) ? 0 : 1);
        return static_cast<int>(operationCount);
    }
};

}

namespace FindMinOpsMakeElementsDivisibleBy3Task
{

TEST(FindMinOpsMakeElementsDivisibleBy3TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumOperations({1, 2, 3, 4}));
    ASSERT_EQ(0, solution.minimumOperations({3, 6, 9}));
}

}