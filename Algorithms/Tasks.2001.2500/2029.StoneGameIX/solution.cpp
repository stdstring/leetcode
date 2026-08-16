#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool stoneGameIX(std::vector<int> const &stones) const
    {
        // without values divisible by 3
        // 1(A) -> 1(B) -> 2(A) -> 1(B) -> ...
        // 2(A) -> 2(B) -> 1(A) -> 2(B) -> ...
        // so frequency[1] > 0 and frequency[2] > 0 for Alice win
        // if count of values divisible by 3 is even
        // then Alice and Bob each get the same number of extra turns, leaving the game state unchanged
        // so frequency[1] > 0 and frequency[2] > 0 for Alice win
        // if count of values divisible by 3 is odd
        // then Bob has one extra turn to skip his turn
        // 1(A) -> 1(A) -> 2(A) -> 1(B) -> ...
        // 2(A) -> 2(A) -> 1(A) -> 2(B) -> ...
        // so std::abs(frequency[1] - frequency[2]) > 2 for Alice win
        constexpr int divider = 3;
        std::vector<int> restCounts(divider, 0);
        for (const int value : stones)
            ++restCounts[value % divider];
        const bool hasSkip = (restCounts[0] % 2) == 1;
        if (hasSkip)
            return std::abs(restCounts[1] - restCounts[2]) > 2;
        return std::min(restCounts[1], restCounts[2]) > 0;
    }
};

}

namespace StoneGameIXTask
{

TEST(StoneGameIXTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.stoneGameIX({2, 1}));
    ASSERT_EQ(false, solution.stoneGameIX({2}));
    ASSERT_EQ(false, solution.stoneGameIX({5, 1, 2, 4, 3}));
}

TEST(StoneGameIXTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.stoneGameIX({20, 3, 20, 17, 2, 12, 15, 17, 4}));
    ASSERT_EQ(false, solution.stoneGameIX({2, 2, 3}));
    ASSERT_EQ(true, solution.stoneGameIX({19, 2, 17, 20, 7, 17}));
    ASSERT_EQ(false, solution.stoneGameIX({2, 3}));
    ASSERT_EQ(false, solution.stoneGameIX({1, 3}));
}

}