#include <algorithm>
#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSumSubmatrix(std::vector<std::vector<int>> const &matrix, int k) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::vector<std::vector<int>> rowPrefixSums(rowCount, std::vector<int>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                rowPrefixSums[row][column] = matrix[row][column] + (column > 0 ? rowPrefixSums[row][column - 1] : 0);
        }
        int maxSum = INT_MIN;
        for (size_t startColumn = 0; startColumn < columnCount; ++startColumn)
        {
            for (size_t endColumn = startColumn; endColumn < columnCount; ++endColumn)
            {
                std::set<int> knownSums;
                knownSums.emplace(0);
                int currentSum = 0;
                for (size_t row = 0; row < rowCount; ++row)
                {
                    currentSum += (rowPrefixSums[row][endColumn] - (startColumn > 0 ? rowPrefixSums[row][startColumn - 1] : 0));
                    // currentSum - prevSum <= k
                    const int prevSumBound = currentSum - k;
                    auto iterator = knownSums.lower_bound(prevSumBound);
                    if (iterator != knownSums.cend())
                    {
                        if (*iterator == prevSumBound)
                            return k;
                        maxSum = std::max(maxSum, currentSum - *iterator);
                    }
                    knownSums.emplace(currentSum);
                }
            }
        }
        return maxSum;
    }
};

}

namespace MaxSumOfRectangleNoLargerThanKTask
{

TEST(MaxSumOfRectangleNoLargerThanKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxSumSubmatrix({{1, 0, 1}, {0, -2, 3}}, 2));
    ASSERT_EQ(3, solution.maxSumSubmatrix({{2, 2, -1}}, 3));
}

TEST(MaxSumOfRectangleNoLargerThanKTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(-1, solution.maxSumSubmatrix({{2, 2, -1}}, 0));
    ASSERT_EQ(2, solution.maxSumSubmatrix({{5, -4, -3, 4}, {-3, -4, 4, 5}, {5, 1, 5, -4}}, 3));
}

}