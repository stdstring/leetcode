#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minDistance(std::string const &word1, std::string const &word2) const
    {
        // calculate Longest Common Subsequence
        std::vector<size_t> prevRow(word2.size(), 0);
        std::vector<size_t> currentRow(word2.size(), 0);
        for (size_t index1 = 0; index1 < word1.size(); ++index1)
        {
            std::swap(prevRow, currentRow);
            for (size_t index2 = 0; index2 < word2.size(); ++index2)
            {
                if (word1[index1] == word2[index2])
                    currentRow[index2] = 1 + (index1 == 0 || index2 == 0 ? 0 : prevRow[index2 - 1]);
                else
                    currentRow[index2] = std::max(index1 == 0 ? 0 : prevRow[index2], index2 == 0 ? 0 : currentRow[index2 - 1]);
            }
        }
        return static_cast<int>(word1.size() + word2.size() - 2 * currentRow.back());
    }
};

}

namespace DeleteOperationForTwoStringsTask
{

TEST(DeleteOperationForTwoStringsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.minDistance("sea", "eat"));
    ASSERT_EQ(4, solution.minDistance("leetcode", "etco"));
}

}