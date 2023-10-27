#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool hasValidPath(std::vector<std::vector<char>> const &grid) const
    {
        if (grid[0][0] == ')')
            return false;
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        const size_t maxSequenceSize = rowCount + columnCount - 1;
        std::vector<std::vector<std::vector<bool>>> dp(rowCount, std::vector<std::vector<bool>>(columnCount, std::vector<bool>(maxSequenceSize, false)));
        dp[0][0][1] = true;
        for (size_t index = 1; index < rowCount + columnCount; ++index)
        {
            const size_t startRow = index <= rowCount ? index - 1 : rowCount - 1;
            const size_t startColumn = index <= rowCount ? 0 : index - rowCount;
            const size_t frontDelta = std::min(startRow + 1, columnCount - startColumn);
            for (size_t frontIndex = 0; frontIndex < frontDelta; ++frontIndex)
            {
                const size_t row = startRow - frontIndex;
                const size_t column = startColumn + frontIndex;
                for (size_t sizeIndex = 0; sizeIndex < maxSequenceSize; ++sizeIndex)
                {
                    if (!dp[row][column][sizeIndex])
                        continue;
                    if (row < rowMax)
                    {
                        const int delta = grid[row + 1][column] == '(' ? 1 : -1;
                        if ((sizeIndex > 0) || (delta > 0))
                            dp[row + 1][column][sizeIndex + delta] = true;
                    }
                    if (column < columnMax)
                    {
                        const int delta = grid[row][column + 1] == '(' ? 1 : -1;
                        if ((sizeIndex > 0) || (delta > 0))
                            dp[row][column + 1][sizeIndex + delta] = true;
                    }
                }
            }
        }
        return dp.back().back()[0];
    }
};

}

namespace CheckIfThereValidParenthesesPathTask
{

TEST(CheckIfThereValidParenthesesPathTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.hasValidPath({{'(', '(', '('}, {')', '(', ')'}, {'(', '(', ')'}, {'(', '(', ')'}}));
    ASSERT_EQ(false, solution.hasValidPath({{')', ')'}, {'(', '('}}));
}

}