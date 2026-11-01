#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minMoves(std::vector<int> const &nums) const
    {
        // There are n elements; let the minimum element is a(1).
        // We set the solution is m, after m moves, all the elements will be the same value,
        // that is a(1) + m, so the other(n - 1) element will add a(1) + m - a(i) times.
        // We know that m moves will introduce m * (n - 1) to the array's total sums.
        // We can have the equation:
        // m * (n - 1) = m + a(1) + m - a(2) + a(1) + m - a(3) + ... + a(1) + m - a(n)
        // = > m * n - m = m * n + (n - 1) * a(1) - a(2) - a(3) - ... - a(n)
        // = > m = a(2) + a(3) + ... + a(n) - (n - 1) * a(1)
        // = > m = Sum - n * Min
        const long long minValue = std::ranges::min(nums);
        const long long sum = std::accumulate(nums.cbegin(), nums.cend(), 0LL);
        const long long result = sum - static_cast<long long>(nums.size()) * minValue;
        return static_cast<int>(result);
    }
};

}

namespace MinMovesToEqualArrayElementsTask
{

TEST(MinMovesToEqualArrayElementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minMoves({1, 2, 3}));
    ASSERT_EQ(0, solution.minMoves({1, 1, 1}));
}

TEST(MinMovesToEqualArrayElementsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minMoves({1, 2}));
    ASSERT_EQ(300, solution.minMoves({-100, 0, 100}));
}

}