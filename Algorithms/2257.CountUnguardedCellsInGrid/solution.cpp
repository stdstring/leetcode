#include <vector>

#include "gtest/gtest.h"

namespace
{

enum class CellState {Empty, Occupied, Guarded};

class Solution
{
public:
    [[nodiscard]] int countUnguarded(int m, int n, std::vector<std::vector<int>> const &guards, std::vector<std::vector<int>> const &walls) const
    {
        std::vector<CellState> board(1ULL * m * n, CellState::Empty);
        size_t freeCells = 1ULL * m * n;
        for (std::vector<int> const &wall : walls)
        {
            board[wall[0] * n + wall[1]] = CellState::Occupied;
            --freeCells;
        }
        for (std::vector<int> const &guard : guards)
        {
            --freeCells;
            board[guard[0] * n + guard[1]] = CellState::Occupied;
        }
        for (std::vector<int> const &guard : guards)
        {
            for (int shift = 1; shift <= guard[1]; ++shift)
            {
                const size_t cell = guard[0] * n + (guard[1] - shift);
                if (board[cell] == CellState::Occupied)
                    break;
                freeCells = processCellByGuard(board, cell, freeCells);
            }
            for (int shift = 1; shift < n - guard[1]; ++shift)
            {
                const size_t cell = guard[0] * n + (guard[1] + shift);
                if (board[cell] == CellState::Occupied)
                    break;
                freeCells = processCellByGuard(board, cell, freeCells);
            }
            for (int shift = 1; shift <= guard[0]; ++shift)
            {
                const size_t cell = (guard[0] - shift) * n + guard[1];
                if (board[cell] == CellState::Occupied)
                    break;
                freeCells = processCellByGuard(board, cell, freeCells);
            }
            for (int shift = 1; shift < m - guard[0]; ++shift)
            {
                const size_t cell = (guard[0] + shift) * n + guard[1];
                if (board[cell] == CellState::Occupied)
                    break;
                freeCells = processCellByGuard(board, cell, freeCells);
            }
        }
        return static_cast<int>(freeCells);
    }

private:
    size_t processCellByGuard(std::vector<CellState> &board, size_t cell, size_t freeCells) const
    {
        if (board[cell] == CellState::Empty)
        {
            board[cell] = CellState::Guarded;
            --freeCells;
        }
        return freeCells;
    }
};

}

namespace CountUnguardedCellsInGridTask
{

TEST(CountUnguardedCellsInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.countUnguarded(4, 6, {{0, 0}, {1, 1}, {2, 3}}, {{0, 1}, {2, 2}, {1, 4}}));
    ASSERT_EQ(4, solution.countUnguarded(3, 3, {{1, 1}}, {{0, 1}, {1, 0}, {2, 1}, {1, 2}}));
}

TEST(CountUnguardedCellsInGridTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.countUnguarded(2, 7, {{1, 5}, {1, 1}, {1, 6}, {0, 2}}, {{0, 6}, {0, 3}, {0, 5}}));
}

}