#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxEqualRowsAfterFlips(std::vector<std::vector<int>> const &matrix) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::unordered_map<std::string, size_t> patternMap;
        for (size_t row = 0; row < rowCount; ++row)
        {
            std::string rowDescriptor;
            for (size_t column = 0; column < columnCount; ++column)
            {
                rowDescriptor.push_back(matrix[row][column] == matrix[row][0] ? '1' : '0');
            }
            ++patternMap[rowDescriptor];
        }
        size_t maxEqualRows = 0;
        for (auto const &[_, equalRowsCount] : patternMap)
            maxEqualRows = std::max(maxEqualRows, equalRowsCount);
        return static_cast<int>(maxEqualRows);
    }
};

}

namespace FlipColumnsForMaxNumberEqualRowsTask
{

TEST(FlipColumnsForMaxNumberEqualRowsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.maxEqualRowsAfterFlips({{0, 1}, {1, 1}}));
    ASSERT_EQ(2, solution.maxEqualRowsAfterFlips({{0, 1}, {1, 0}}));
    ASSERT_EQ(2, solution.maxEqualRowsAfterFlips({{0, 0, 0}, {0, 0, 1}, {1, 1, 0}}));
}

}