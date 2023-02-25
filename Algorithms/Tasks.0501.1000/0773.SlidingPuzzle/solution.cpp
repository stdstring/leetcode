#include <queue>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int slidingPuzzle(std::vector<std::vector<int>> const &board) const
    {
        int result = 0;
        for (std::vector<int> const &row : board)
        {
            for (int value : row)
                result = 10 * result + value;
        }
        int initialMove = 123450;
        if (initialMove == result)
            return 0;
        std::queue<std::pair<int, size_t>> moves;
        moves.emplace(initialMove, 0);
        std::unordered_set<int> knownMoves;
        knownMoves.insert(initialMove);
        while (!moves.empty())
        {
            for (int nextMove : calcNextMoves(moves.front().first))
            {
                if (nextMove == result)
                    return static_cast<int>(moves.front().second + 1);
                if (knownMoves.count(nextMove) == 0)
                {
                    moves.emplace(nextMove, moves.front().second + 1);
                    knownMoves.insert(nextMove);
                }
            }
            moves.pop();
        }
        return -1;
    }

private:
    int calcMove(int value1, int value2, int value3, int value4, int value5, int value6) const
    {
        return value1 * 100000 + value2 * 10000 + value3 * 1000 + value4 * 100 + value5 * 10 + value6;
    }

    std::vector<int> calcNextMoves(int currentMove) const
    {
        const int value6 = currentMove % 10;
        currentMove /= 10;
        const int value5 = currentMove % 10;
        currentMove /= 10;
        const int value4 = currentMove % 10;
        currentMove /= 10;
        const int value3 = currentMove % 10;
        currentMove /= 10;
        const int value2 = currentMove % 10;
        const int value1 = currentMove / 10;
        if (value6 == 0)
            return {calcMove(value1, value2, value3, value4, 0, value5), calcMove(value1, value2, 0, value4, value5, value3)};
        if (value5 == 0)
            return {calcMove(value1, value2, value3, 0, value4, value6),
                    calcMove(value1, value2, value3, value4, value6, 0),
                    calcMove(value1, 0, value3, value4, value2, value6)};
        if (value4 == 0)
            return {calcMove(value1, value2, value3, value5, 0, value6), calcMove(0, value2, value3, value1, value5, value6)};
        if (value3 == 0)
            return {calcMove(value1, value2, value6, value4, value5, 0), calcMove(value1, 0, value2, value4, value5, value6)};
        if (value2 == 0)
            return {calcMove(0, value1, value3, value4, value5, value6),
                    calcMove(value1, value3, 0, value4, value5, value6),
                    calcMove(value1, value5, value3, value4, 0, value6)};
        if (value1 == 0)
            return {calcMove(value2, 0, value3, value4, value5, value6), calcMove(value4, value2, value3, 0, value5, value6)};
        return {};
    }
};

}

namespace SlidingPuzzleTask
{

TEST(SlidingPuzzleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.slidingPuzzle({{1, 2, 3}, {4, 0, 5}}));
    ASSERT_EQ(-1, solution.slidingPuzzle({{1, 2, 3}, {5, 4, 0}}));
    ASSERT_EQ(5, solution.slidingPuzzle({{4, 1, 2}, {5, 0, 3}}));
    ASSERT_EQ(14, solution.slidingPuzzle({{3, 2, 4}, {1, 5, 0}}));
}

}