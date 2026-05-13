#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minMoves(std::vector<int> const &nums, int limit) const
    {
        // let (a, b) - pair, a + b = c
        // range for c : [2, 2*limit]
        // when 2 <= c < a + 1 : 2 operations are required
        // when a + 1 <= c < a + b: 1 operation is required
        // when c = a + b: no modifications are required
        // when a + b < c <= b + limit: 1 operation is required
        // when b + limit < c <= 2*limit: 2 operations are required
        const int n = static_cast<int>(nums.size());
        std::vector<int> diff(2 + 2 * limit, 0);
        for (int left = 0, right = n - 1; left < right; ++left, --right)
        {
            const int a = std::min(nums[left], nums[right]);
            const int b = std::max(nums[left], nums[right]);
            diff[2] += 2;
            diff[a + 1] -= 1;
            diff[a + b] -= 1;
            diff[a + b + 1] += 1;
            diff[b + limit + 1] += 1;
        }
        int bestMoves = n;
        int currentMoves = 0;
        for (int c = 2; c <= 2 * limit; ++c)
        {
            currentMoves += diff[c];
            bestMoves = std::min(bestMoves, currentMoves);
        }
        return bestMoves;
    }
};

}

namespace MinMovesMakeArrayComplementaryTask
{

TEST(MinMovesMakeArrayComplementaryTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minMoves({1, 2, 4, 3}, 4));
    ASSERT_EQ(2, solution.minMoves({1, 2, 2, 1}, 2));
    ASSERT_EQ(0, solution.minMoves({1, 2, 1, 2}, 2));
}

}