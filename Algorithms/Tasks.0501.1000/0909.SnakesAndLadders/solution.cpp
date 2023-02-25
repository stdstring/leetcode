#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int snakesAndLadders(std::vector<std::vector<int>> const &board) const
    {
        const size_t n = board.size();
        const size_t size =  n * n;
        std::vector<std::pair<size_t, size_t>> boardCoords(createBoardCoords(static_cast<int>(n)));
        std::vector<bool> visitedNumbers(size, false);
        visitedNumbers[0] = true;
        std::queue<std::pair<size_t, size_t>> numbers;
        numbers.emplace(1, 0);
        while (!numbers.empty())
        {
            auto [current, currentPath] = numbers.front();
            if (current == size)
                return static_cast<int>(currentPath);
            numbers.pop();
            size_t nextPath = currentPath + 1;
            for (size_t next = current + 1; next <= std::min(current + 6, size); ++next)
            {
                if (visitedNumbers[next - 1])
                    continue;
                visitedNumbers[next - 1] = true;
                auto [row, column] = boardCoords[next - 1];
                int cellValue = board[row][column];
                if (cellValue == -1)
                    numbers.emplace(next, nextPath);
                else
                    numbers.emplace(cellValue, nextPath);
            }
        }
        return -1;
    }

private:
    [[nodiscard]] std::vector<std::pair<size_t, size_t>> createBoardCoords(int n) const
    {
        std::vector<std::pair<size_t, size_t>> boardCoords;
        int row = n - 1;
        int column = 0;
        int columnDelta = 1;
        for (int number = 1; number <= n * n; ++number)
        {
            boardCoords.emplace_back(row, column);
            if (((column == 0) && (columnDelta == -1)) || ((column == n - 1) && (columnDelta == 1)))
            {
                --row;
                columnDelta = -columnDelta;
            }
            else
                column += columnDelta;
        }
        return boardCoords;
    }
};

}

namespace SnakesAndLaddersTask
{

TEST(SnakesAndLaddersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.snakesAndLadders({{-1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1},
                                            {-1, 35, -1, -1, 13, -1},
                                            {-1, -1, -1, -1, -1, -1},
                                            {-1, 15, -1, -1, -1, -1}}));
    ASSERT_EQ(1, solution.snakesAndLadders({{-1, -1}, {-1, 3}}));
}

TEST(SnakesAndLaddersTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(-1, solution.snakesAndLadders({{1, 1, -1}, {1, 1, 1}, {-1, 1, 1}}));
    ASSERT_EQ(3, solution.snakesAndLadders({{-1, 33, -1, -1, -1, -1, -1, -1},
                                            {5, -1, -1, -1, -1, 49, -1, -1},
                                            {-1, -1, -1, 31, -1, -1, 54, 43},
                                            {-1, -1, 26, 13, 41, -1, -1, -1},
                                            {-1, -1, -1, -1, 14, 45, 23, 2},
                                            {30, 33, -1, -1, -1, -1, 31, -1},
                                            {17, 49, -1, -1, -1, -1, -1, -1},
                                            {-1, 56, 12, 47, -1, -1, -1, -1}}));
    ASSERT_EQ(4, solution.snakesAndLadders({{-1, -1, -1, 46, 47, -1, -1, -1},
                                            {51, -1, -1, 63, -1, 31, 21, -1},
                                            {-1, -1, 26, -1, -1, 38, -1, -1},
                                            {-1, -1, 11, -1, 14, 23, 56, 57},
                                            {11, -1, -1, -1, 49, 36, -1, 48},
                                            {-1, -1, -1, 33, 56, -1, 57, 21},
                                            {-1, -1, -1, -1, -1, -1, 2, -1},
                                            {-1, -1, -1, 8, 3, -1, 6, 56}}));
    ASSERT_EQ(3, solution.snakesAndLadders({{-1, -1, 46, -1, 42, -1, -1, -1, -1},
                                            {-1, 53, 65, 57, -1, -1, 16, -1, 7},
                                            {-1, -1, -1, -1, -1, -1, 43, -1, -1},
                                            {29, -1, 63, -1, -1, -1, -1, 12, -1},
                                            {-1, 40, -1, -1, -1, -1, -1, -1, -1},
                                            {-1, -1, -1, -1, -1, -1, -1, 14, -1},
                                            {-1, 6, -1, -1, 10, -1, 12, -1, 78},
                                            {46, -1, 3, -1, 41, -1, 20, 79, -1},
                                            {-1, -1, 45, 32, -1, -1, -1, -1, 60}}));
    ASSERT_EQ(10, solution.snakesAndLadders({{-1, -1, -1, 135, -1, -1, -1, -1, -1, 185, -1, -1, -1, -1, 105, -1},
                                             {-1, -1, 92, -1, -1, -1, -1, -1, -1, 201, -1, 118, -1, -1, 183, -1},
                                             {-1, -1, -1, -1, -1, -1, -1, -1, -1, 179, -1, -1, -1, -1, -1, -1},
                                             {-1, 248, -1, -1, -1, -1, -1, -1, -1, 119, -1, -1, -1, -1, -1, 192},
                                             {-1, -1, 104, -1, -1, -1, -1, -1, -1, -1, 165, -1, -1, 206, 104, -1},
                                             {145, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 229, -1},
                                             {-1, -1, 75, 140, -1, -1, -1, -1, -1, -1, -1, -1, 43, -1, 34, -1},
                                             {-1, -1, -1, -1, -1, -1, 169, -1, -1, -1, -1, -1, -1, 188, -1, -1},
                                             {-1, -1, -1, -1, -1, -1, 92, -1, 171, -1, -1, -1, -1, -1, -1, 66},
                                             {-1, -1, -1, 126, -1, -1, 68, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                             {-1, 109, -1, 86, 28, 228, -1, -1, 144, -1, -1, -1, -1, -1, -1, -1},
                                             {-1, -1, -1, -1, 59, -1, -1, -1, -1, -1, 51, -1, -1, -1, 62, -1},
                                             {-1, 71, -1, -1, -1, 63, -1, -1, -1, -1, -1, -1, 212, -1, -1, -1},
                                             {-1, -1, -1, -1, 174, -1, 59, -1, -1, -1, -1, -1, -1, 133, -1, -1},
                                             {-1, -1, 62, -1, 5, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                             {-1, -1, -1, 59, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}}));
}


}