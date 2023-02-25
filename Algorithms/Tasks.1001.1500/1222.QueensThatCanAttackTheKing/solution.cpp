#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

enum class Direction {Unknown, N, W, E, S, NW, NE, SW, SE};

class Solution
{
public:
    std::vector<std::vector<int>> queensAttacktheKing(std::vector<std::vector<int>> const &queens, std::vector<int> const &king) const
    {
        std::unordered_map<Direction, std::vector<int>> attackingQueens;
        for (std::vector<int> const &queen : queens)
        {
            Direction direction = calcQueenDirection(queen, king);
            switch (direction)
            {
                case Direction::N:
                case Direction::NW:
                case Direction::NE:
                    if (attackingQueens.count(direction) == 0 || (king[0] - queen[0]) < (king[0] - attackingQueens[direction][0]))
                        attackingQueens[direction] = queen;
                    break;
                case Direction::S:
                case Direction::SW:
                case Direction::SE:
                    if (attackingQueens.count(direction) == 0 || (queen[0] - king[0]) < (attackingQueens[direction][0] - king[0]))
                        attackingQueens[direction] = queen;
                    break;
                case Direction::W:
                    if (attackingQueens.count(direction) == 0 || (king[1] - queen[1]) < (king[1] - attackingQueens[direction][1]))
                        attackingQueens[direction] = queen;
                    break;
                case Direction::E:
                    if (attackingQueens.count(direction) == 0 || (queen[1] - king[1]) < (attackingQueens[direction][1] - king[1]))
                        attackingQueens[direction] = queen;
                    break;
                case Direction::Unknown:
                    break;
            }
        }
        std::vector<std::vector<int>> result;
        for (Direction direction : {Direction::NW, Direction::N, Direction::NE, Direction::E, Direction::SE, Direction::S, Direction::SW, Direction::W})
        {
            if (attackingQueens.count(direction) == 1)
                result.push_back(attackingQueens[direction]);
        }
        return result;
    }

private:
    Direction calcQueenDirection(std::vector<int> const &queen, std::vector<int> const &king) const
    {
        if (queen[0] == king[0])
            return queen[1] < king[1] ? Direction::W : Direction::E;
        if (queen[1] == king[1])
            return queen[0] < king[0] ? Direction::N : Direction::S;
        // straight diagonal
        if ((queen[0] - queen[1]) == (king[0] - king[1]))
            return queen[0] < king[0] ? Direction::NW : Direction::SE;
        // reverse diagonal
        if ((queen[0] + queen[1]) == (king[0] + king[1]))
            return queen[0] < king[0] ? Direction::NE : Direction::SW;
        return Direction::Unknown;
    }
};

}

namespace QueensThatCanAttackTheKingTask
{

TEST(QueensThatCanAttackTheKingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 1}, {3, 3}, {1, 0}}), solution.queensAttacktheKing({{0, 1}, {1, 0}, {4, 0}, {0, 4}, {3, 3}, {2, 4}}, {0, 0}));
    ASSERT_EQ(std::vector<std::vector<int>>({{2, 2}, {3, 4}, {4, 4}}), solution.queensAttacktheKing({{0, 0}, {1, 1}, {2, 2}, {3, 4}, {3, 5}, {4, 4}, {4, 5}}, {3, 3}));
}

}