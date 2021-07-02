#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int knightDialer(int n) const
    {
        constexpr int modValue = 1000000007;
        constexpr size_t digitsCount = 10;
        std::vector<std::vector<size_t>> possibleMoves = {{4, 6}, {6, 8}, {7, 9}, {4, 8}, {0, 3, 9}, {}, {0, 1, 7}, {2, 6}, {1, 3}, {2, 4}};
        std::vector<int> movesCount(digitsCount, 1);
        std::vector<int> nextMovesCount(digitsCount, 0);
        for (size_t step = 2; step <= static_cast<size_t>(n); ++step)
        {
            for (size_t digit = 0; digit < digitsCount; ++digit)
            {
                for (size_t possibleMove : possibleMoves[digit])
                    nextMovesCount[possibleMove] = (nextMovesCount[possibleMove] + movesCount[digit]) % modValue;
            }
            std::swap(nextMovesCount, movesCount);
            for (size_t digit = 0; digit < digitsCount; ++digit)
                nextMovesCount[digit] = 0;
        }
        int result = 0;
        for (size_t digit = 0; digit < digitsCount; ++digit)
            result = (result + movesCount[digit]) % modValue;
        return result;
    }
};

}

namespace KnightDialerTask
{

TEST(KnightDialerTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(10, solution.knightDialer(1));
    ASSERT_EQ(20, solution.knightDialer(2));
    ASSERT_EQ(46, solution.knightDialer(3));
    ASSERT_EQ(104, solution.knightDialer(4));
    ASSERT_EQ(136006598, solution.knightDialer(3131));
}

}