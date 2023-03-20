#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long gridGame(std::vector<std::vector<int>> const &grid) const
    {
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        std::vector<long long> prefixSumsRow0(columnCount, 0);
        std::vector<long long> prefixSumsRow1(columnCount, 0);
        for (size_t index = 0; index < columnCount; ++index)
        {
            prefixSumsRow0[index] = grid[0][index] + (index > 0 ? prefixSumsRow0[index - 1] : 0);
            const size_t rIndex = columnCount - index - 1;
            prefixSumsRow1[rIndex] = grid[1][rIndex] + (index > 0 ? prefixSumsRow1[rIndex + 1] : 0);
        }
        long long maxSecondResult = prefixSumsRow0[columnMax] + prefixSumsRow1[0];
        for (size_t index = 0; index < columnCount; ++index)
        {
            const long long currentSecondResult = std::max(prefixSumsRow0[columnMax] - prefixSumsRow0[index],
                                                           prefixSumsRow1[0] - prefixSumsRow1[index]);
            if (currentSecondResult < maxSecondResult)
                maxSecondResult = currentSecondResult;
        }
        return maxSecondResult;
    }
};

}

namespace GridGameTask
{

TEST(GridGameTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.gridGame({{2, 5, 4}, {1, 5, 1}}));
    ASSERT_EQ(4, solution.gridGame({{3, 3, 1}, {8, 5, 2}}));
    ASSERT_EQ(7, solution.gridGame({{1, 3, 1, 15}, {1, 3, 3, 1}}));
}

TEST(GridGameTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(63, solution.gridGame({{20, 3, 20, 17, 2, 12, 15, 17, 4, 15}, {20, 10, 13, 14, 15, 5, 2, 3, 14, 3}}));
}

}