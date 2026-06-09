#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxTotalValue(std::vector<int> const &nums, int k) const
    {
        auto [minValue, maxValue] = std::ranges::minmax(nums);
        return 1LL * (maxValue - minValue) * k;
    }
};

}

namespace MaxTotalSubarrayValue1Task
{

TEST(MaxTotalSubarrayValue1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxTotalValue({1, 3, 2}, 2));
    ASSERT_EQ(12, solution.maxTotalValue({4, 2, 5, 1}, 3));
}

}