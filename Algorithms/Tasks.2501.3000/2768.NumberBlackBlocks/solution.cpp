#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> countBlackBlocks(int m, int n, std::vector<std::vector<int>> const &coordinates) const
    {
        const int maxRow = m - 1;
        const int maxColumn = n - 1;
        constexpr size_t totalCases = 5; // 0, 1, 2, 3, 4 black cells in block
        const long long totalBlockCount = 1LL * (m - 1) * (n - 1);
        std::vector<long long> result(totalCases, 0);
        result[0] = totalBlockCount;
        std::set<std::pair<int, int>> blackBlocks;
        for (std::vector<int> const& blackBlock : coordinates)
            blackBlocks.emplace(std::pair<int, int>(blackBlock[0], blackBlock[1]));
        for (auto const &[row, column] : blackBlocks)
        {
            if ((row > 0) && (column > 0))
            {
                const size_t blackBlocksCount = calcBlackBlocks(row - 1, column - 1, row, column, blackBlocks);
                ++result[blackBlocksCount];
                --result[0];
            }
            if ((row > 0) && (column < maxColumn))
            {
                const size_t blackBlocksCount = calcBlackBlocks(row - 1, column, row, column, blackBlocks);
                ++result[blackBlocksCount];
                --result[0];
            }
            if ((row < maxRow) && (column > 0))
            {
                const size_t blackBlocksCount = calcBlackBlocks(row, column - 1, row, column, blackBlocks);
                ++result[blackBlocksCount];
                --result[0];
            }
            if ((row < maxRow) && (column < maxColumn))
            {
                const size_t blackBlocksCount = calcBlackBlocks(row, column, row, column, blackBlocks);
                ++result[blackBlocksCount];
                --result[0];
            }
        }
        return result;
    }

private:
    [[nodiscard]] size_t calcBlackBlocks(int topRow, int leftColumn, int row, int column, std::set<std::pair<int, int>> const &blackBlocks) const
    {
        const bool isBlackBlock0 = blackBlocks.contains(std::pair<int, int>(topRow, leftColumn));
        const bool isBlackBlock1 = blackBlocks.contains(std::pair<int, int>(topRow, leftColumn + 1));
        const bool isBlackBlock2 = blackBlocks.contains(std::pair<int, int>(topRow + 1, leftColumn));
        const bool isBlackBlock3 = blackBlocks.contains(std::pair<int, int>(topRow + 1, leftColumn + 1));
        if ((topRow < row) && (leftColumn < column) && (isBlackBlock0 || isBlackBlock1 || isBlackBlock2))
            return 0;
        if ((topRow < row) && (leftColumn == column) && (isBlackBlock0 || isBlackBlock1))
            return 0;
        if ((topRow == row) && (leftColumn < column) && isBlackBlock0)
            return 0;
        return (isBlackBlock0 ? 1 : 0) + (isBlackBlock1 ? 1 : 0) + (isBlackBlock2 ? 1 : 0) + (isBlackBlock3 ? 1 : 0);
    }
};

}

namespace NumberBlackBlocksTask
{

TEST(NumberBlackBlocksTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({3, 1, 0, 0, 0}), solution.countBlackBlocks(3, 3, {{0, 0}}));
    ASSERT_EQ(std::vector<long long>({0, 2, 2, 0, 0}), solution.countBlackBlocks(3, 3, {{0, 0}, {1, 1}, {0, 2}}));
}

TEST(NumberBlackBlocksTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({1503, 130, 5, 0, 0}),
              solution.countBlackBlocks(22, 79, {{11, 43}, {17, 56}, {11, 58}, {19, 68}, {5, 10},
                                                 {18, 35}, {18, 27}, {10, 53}, {1, 72}, {4, 64},
                                                 {4, 72}, {3, 76}, {18, 36}, {14, 47}, {12, 57},
                                                 {10, 11}, {13, 5}, {17, 39}, {1, 4}, {3, 32},
                                                 {6, 34}, {2, 62}, {8, 35}, {9, 18}, {12, 77},
                                                 {8, 43}, {1, 49}, {15, 14}, {15, 27}, {4, 68},
                                                 {19, 24}, {9, 19}, {17, 3}, {3, 51}, {5, 61}}));
}

}