#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximalRectangle(std::vector<std::vector<char>> const &matrix) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        int maxArea = 0;
        std::vector<int> prevBColumn(rowCount, 0);
        for (size_t column = 0; column < columnCount; ++column)
        {
            std::vector<int> currentBColumn(rowCount, 0);
            for (size_t row = 0; row < rowCount; ++row)
                currentBColumn[row] = (matrix[row][column] == '0') ? 0 : (prevBColumn[row] + 1);
            std::vector<int> leftGEValueCounts(rowCount, 0);
            // element, count
            std::stack<std::pair<int, int>> leftStack;
            for (size_t row = 0; row < rowCount; ++row)
            {
                int countBefore = 0;
                while (!leftStack.empty() && (leftStack.top().first >= currentBColumn[row]))
                {
                    countBefore += (leftStack.top().second + 1);
                    leftStack.pop();
                }
                leftStack.emplace(currentBColumn[row], countBefore);
                leftGEValueCounts[row] = countBefore;
            }
            std::vector<int> rightGEValueCounts(rowCount, 0);
            // element, count
            std::stack<std::pair<int, int>> rightStack;
            for (size_t row = 0; row < rowCount; ++row)
            {
                int countAfter = 0;
                while (!rightStack.empty() && (rightStack.top().first >= currentBColumn[rowCount - 1 - row]))
                {
                    countAfter += (rightStack.top().second + 1);
                    rightStack.pop();
                }
                rightStack.emplace(currentBColumn[rowCount - 1 - row], countAfter);
                rightGEValueCounts[rowCount - 1 - row] = countAfter;
            }
            for (size_t row = 0; row < rowCount; ++row)
                maxArea = std::max(maxArea, currentBColumn[row] * (1 + leftGEValueCounts[row] + rightGEValueCounts[row]));
            std::swap(prevBColumn, currentBColumn);
        }
        return maxArea;
    }
};

}

namespace MaximalRectangleTask
{

TEST(MaximalRectangleTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.maximalRectangle({{'1', '0', '1', '0', '0'},
                                            {'1', '0', '1', '1', '1'},
                                            {'1', '1', '1', '1', '1'},
                                            {'1', '0', '0', '1', '0'}}));
    ASSERT_EQ(0, solution.maximalRectangle({{'0'}}));
    ASSERT_EQ(1, solution.maximalRectangle({{'1'}}));
}

TEST(MaximalRectangleTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.maximalRectangle({{'0', '1', '0', '1', '1', '1', '1'},
                                             {'0', '1', '1', '1', '1', '0', '0'},
                                             {'1', '0', '1', '1', '1', '1', '1'},
                                             {'1', '1', '1', '1', '1', '1', '1'},
                                             {'1', '0', '1', '1', '1', '1', '1'},
                                             {'1', '1', '0', '0', '1', '1', '0'}}));
}

}