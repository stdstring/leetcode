#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) const
    {
        // (a, b) denotes the position of the white rook.
        // (c, d) denotes the position of the white bishop.
        // (e, f) denotes the position of the black queen.
        // check row
        if (a == e)
            return (c != a) || (d < std::min(b, f)) || (d > std::max(b, f)) ? 1 : 2;
        // check column
        if (b == f)
            return (d != b) || (c < std::min(a, e)) || (c > std::max(a, e)) ? 1 : 2;
        // check direct diagonal
        const int rockDirectDiagonal = a - b;
        const int bishopDirectDiagonal = c - d;
        const int queenDirectDiagonal = e - f;
        if (bishopDirectDiagonal == queenDirectDiagonal)
            return (rockDirectDiagonal != queenDirectDiagonal) || (a < std::min(c, e)) || (a > std::max(c, e)) ? 1 : 2;
        // check reverse diagonal
        const int rockReverseDiagonal = a + b;
        const int bishopReverseDiagonal = c + d;
        const int queenReverseDiagonal = e + f;
        if (bishopReverseDiagonal == queenReverseDiagonal)
            return (rockReverseDiagonal != queenReverseDiagonal) || (a < std::min(c, e)) || (a > std::max(c, e)) ? 1 : 2;
        return 2;
    }
};

}

namespace MinMovesToCaptureQueenTask
{

TEST(MinMovesToCaptureQueenTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minMovesToCaptureTheQueen(1, 1, 8, 8, 2, 3));
    ASSERT_EQ(1, solution.minMovesToCaptureTheQueen(5, 3, 3, 4, 5, 2));
}

}