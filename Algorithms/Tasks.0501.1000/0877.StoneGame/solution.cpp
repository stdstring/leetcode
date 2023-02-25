#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool stoneGameDP(std::vector<int> const &piles) const
    {
        // Let's change the game so that whenever Lee scores points, it deducts from Alex's score instead.
        // Let dp(i, j) be the largest score Alex can achieve where the piles remaining are piles[i], piles[i + 1], ..., piles[j].
        // This is natural in games with scoring : we want to know what the value of each position of the game is.
        // We can formulate a recursion for dp(i, j) in terms of dp(i + 1, j) and dp(i, j - 1), and we can use dynamic programming to not repeat work in this recursion.
        // This approach can output the correct answer, because the states form a DAG(directed acyclic graph).
        // When the piles remaining are piles[i], piles[i + 1], ..., piles[j], the player who's turn it is has at most 2 moves.
        // The person who's turn it is can be found by comparing j - i to N modulo 2.
        // If the player is Alex, then she either takes piles[i] or piles[j], increasing her score by that amount.
        // Afterwards, the total score is either piles[i] + dp(i + 1, j), or piles[j] + dp(i, j - 1); and we want the maximum possible score.
        // If the player is Lee, then he either takes piles[i] or piles[j], decreasing Alex's score by that amount.
        // Afterwards, the total score is either -piles[i] + dp(i + 1, j), or -piles[j] + dp(i, j - 1); and we want the minimum possible score.
        const size_t count = piles.size();
        std::vector<std::vector<size_t>> dp(count + 2, std::vector<size_t>(count + 2, 0));
        for (size_t size = 1; size <= count; ++size)
        {
            const bool firstPlayerMove = size % 2 == 0;
            for (size_t i = 0, j = size - 1; j < count; ++i, ++j)
            {
                if (firstPlayerMove)
                    dp[i + 1][j + 1] = std::max(piles[i] + dp[i + 2][j + 1], piles[j] + dp[i + 1][j]);
                else
                    dp[i + 1][j + 1] = std::min(-piles[i] + dp[i + 2][j + 1], -piles[j] + dp[i + 1][j]);
            }
        }
        return dp[1][count] > 0;
    }

    bool stoneGameMath(std::vector<int> const &piles) const
    {
        // Alex clearly always wins the 2 pile game. With some effort, we can see that she always wins the 4 pile game.
        // If Alex takes the first pile initially, she can always take the third pile. If she takes the fourth pile initially, she can always take the second pile.
        // At least one of first + third, second + fourth is larger, so she can always win.
        // We can extend this idea to N piles.Say the first, third, fifth, seventh, etc.piles are white, and the second, fourth, sixth, eighth, etc.piles are black.
        // Alex can always take either all white piles or all black piles, and one of the colors must have a sum number of stones larger than the other color.
        // Hence, Alex always wins the game.
        return true;
    }
};

}

namespace StoneGameTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.stoneGameDP({5, 3, 4, 5}));
    ASSERT_EQ(true, solution.stoneGameMath({5, 3, 4, 5}));
}


}