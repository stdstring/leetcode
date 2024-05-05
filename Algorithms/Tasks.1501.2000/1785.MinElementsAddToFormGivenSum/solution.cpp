#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minElements(std::vector<int> const &nums, int limit, int goal) const
    {
        const long long totalSum = std::accumulate(nums.cbegin(), nums.cend(), 0LL);
        const long long delta = std::abs(goal - totalSum);
        return static_cast<int>((delta / limit) + ((delta % limit) != 0 ? 1 : 0));
    }
};

}

namespace MinElementsAddToFormGivenSumTask
{

TEST(MinElementsAddToFormGivenSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minElements({1, -1, 1}, 3, -4));
    ASSERT_EQ(1, solution.minElements({1, -10, 9, 1}, 100, 0));
}

}