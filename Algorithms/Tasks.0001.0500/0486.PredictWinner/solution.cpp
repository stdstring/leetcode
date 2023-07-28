#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool PredictTheWinner(std::vector<int> const &nums) const
    {
        // Approach 1
        // F(i, j) represents the maximum value the user can collect from i-th coin to j-th coin.
        // arr[] represents the list of coins
        // F(i, j) = Max(Sum - F(i + 1, j, Sum - arr[i]), Sum - F(i, j - 1, Sum - arr[j]))
        // Base Case: F(i, j) = max(arr[i], arr[j]), if j == i + 1
        // Approach 2
        // If we denote the coins collected by us as a positive score of an equivalent amount,
        // whereas the coins removed by our opponent with a negative score of an equivalent amount,
        // then the problem transforms to maximizing our score if we go first.
        // Let us denote dp[i][j] as the maximum score a player can get in the subarray[i ... j],
        // then dp[i][j] = max(arr[i] - dp[i + 1][j], arr[j] - dp[i][j - 1])
        // This relation holds because
        // * If we pick the leftmost element, then we would get a score equivalent to
        //   arr[i] - the maximum amount our opponent can get from the subarray [(i + 1) ... j].
        // * Similarly picking the rightmost element will get us a score equivalent to
        //   arr[j] - the maximum amount of score our opponent gets from the subarray [i ... (j - 1)].
        // This can be solved using the simple Dynamic Programming relation given above. The final answer would be contained in dp[0][n - 1].
        // However, we still need to account for the impact of introducing the negative score.
        // Suppose dp[0][n - 1] equals VAL, the sum of all the scores equals SUM, and the total score of our opponent equals OPP,
        // * Then according to the original problem we are supposed to calculate abs(OPP) + VAL
        //   since our opponent does not have any negative impact on our final answer according to the original problem statement.
        // * This value can be easily calculated as, VAL + 2 * abs(OPP) = SUM
        //   (OPP removed by our opponent implies that we had gained OPP amount as well, hence the 2 * abs(OPP)) = > VAL + abs(OPP) = (SUM + VAL) / 2
        std::vector<std::vector<int>> dp(nums.size(), std::vector<int>(nums.size(), 0));
        for (size_t shift = 0; shift < nums.size(); ++shift)
        {
            const size_t i = nums.size() - 1 - shift;
            for (size_t j = i; j < nums.size(); ++j)
            {
                if (i == j)
                    dp[i][j] = nums[i];
                else
                    dp[i][j] = std::max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }
        return dp[0][nums.size() - 1] >= 0;
    }
};

}

namespace PredictWinnerTask
{

TEST(PredictWinnerTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.PredictTheWinner({1, 5, 2}));
    ASSERT_EQ(true, solution.PredictTheWinner({1, 5, 233, 7}));
}

}