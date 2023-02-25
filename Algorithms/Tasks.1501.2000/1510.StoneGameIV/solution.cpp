#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool winnerSquareGame(int n) const
    {
        std::vector<int> squares;
        for (int number = 1; number * number <= n; ++number)
            squares.push_back(number * number);
        if (squares.back() == n)
            return true;
        std::vector<bool> positions(1LL + n, false);
        for (int number = 1; number <= n; ++number)
        {
            bool result = false;
            for (size_t squareIndex = 0; (squareIndex < squares.size()) && (squares[squareIndex] <= number); ++squareIndex)
            {
                if (!positions[0LL + number - squares[squareIndex]])
                {
                    result = true;
                    break;
                }
            }
            positions[number] = result;
        }
        return positions[n];
    }
};

}

namespace StoneGameIVTask
{

TEST(StoneGameIVTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.winnerSquareGame(1));
    ASSERT_EQ(false, solution.winnerSquareGame(2));
    ASSERT_EQ(true, solution.winnerSquareGame(4));
}

}