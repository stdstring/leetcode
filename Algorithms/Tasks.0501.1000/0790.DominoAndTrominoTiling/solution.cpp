#include <array>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numTilings(int n) const
    {
        constexpr int modValue = 1000000007;
        constexpr size_t linesCount = 3;
        constexpr size_t activeLine = 0, nextLine = 1, afterNextLine = 2;
        constexpr size_t configCount = 3;
        constexpr size_t flatEdge = 0, UpperSticksOut = 1, LowerSticksOut = 2;
        std::array<std::array<size_t, configCount>, linesCount> tiling{};
        // init
        tiling[activeLine][flatEdge] = 1;
        tiling[activeLine][UpperSticksOut] = 1;
        tiling[activeLine][LowerSticksOut] = 1;
        tiling[nextLine][flatEdge] = 1;
        for (int size = 1; size < n; ++size)
        {
            // add vertical domino
            tiling[nextLine][flatEdge] = (tiling[nextLine][flatEdge] + tiling[activeLine][flatEdge]) % modValue;
            // add 2 horizontal domino
            tiling[afterNextLine][flatEdge] = (tiling[afterNextLine][flatEdge] + tiling[activeLine][flatEdge]) % modValue;
            // add tromino
            tiling[nextLine][UpperSticksOut] = (tiling[nextLine][UpperSticksOut] + tiling[activeLine][flatEdge]) % modValue;
            tiling[nextLine][LowerSticksOut] = (tiling[nextLine][LowerSticksOut] + tiling[activeLine][flatEdge]) % modValue;
            tiling[afterNextLine][flatEdge] = (tiling[afterNextLine][flatEdge] + tiling[activeLine][UpperSticksOut]) % modValue;
            tiling[afterNextLine][flatEdge] = (tiling[afterNextLine][flatEdge] + tiling[activeLine][LowerSticksOut]) % modValue;
            // add horizontal domino to tromino
            tiling[nextLine][UpperSticksOut] = (tiling[nextLine][UpperSticksOut] + tiling[activeLine][LowerSticksOut]) % modValue;
            tiling[nextLine][LowerSticksOut] = (tiling[nextLine][LowerSticksOut] + tiling[activeLine][UpperSticksOut]) % modValue;
            std::swap(tiling[activeLine], tiling[nextLine]);
            std::swap(tiling[nextLine], tiling[afterNextLine]);
            tiling[afterNextLine].fill(0);
        }
        return static_cast<int>(tiling[activeLine][flatEdge]);
    }
};

}

namespace DominoAndTrominoTilingTask
{

TEST(DominoAndTrominoTilingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.numTilings(3));
}

TEST(DominoAndTrominoTilingTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(1, solution.numTilings(1));
}

}