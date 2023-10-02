#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool winnerOfGame(std::string const &colors) const
    {
        size_t aliceMoves = 0;
        size_t bobMoves = 0;
        for (size_t index = 1; index < colors.size() - 1; ++index)
        {
            const char prevChar = colors[index - 1];
            const char currentChar = colors[index];
            const char nextChar = colors[index + 1];
            if ((prevChar != currentChar) || (currentChar != nextChar))
                continue;
            ++(currentChar == 'A' ? aliceMoves : bobMoves);
        }
        return aliceMoves > bobMoves;
    }
};

}

namespace RemoveColoredPiecesIfBothNeighborsSameTask
{

TEST(RemoveColoredPiecesIfBothNeighborsSameTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.winnerOfGame("AAABABB"));
    ASSERT_EQ(false, solution.winnerOfGame("AA"));
    ASSERT_EQ(false, solution.winnerOfGame("ABBBBBBBAAA"));
}

}