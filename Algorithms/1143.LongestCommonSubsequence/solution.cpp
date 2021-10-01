#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int longestCommonSubsequence(std::string const &text1, std::string const &text2) const
    {
        std::vector<size_t> currentRow(text2.size());
        for (size_t index1 = 0; index1 < text1.size(); ++index1)
        {
            std::vector<size_t> nextRow(text2.size());
            for (size_t index2 = 0; index2 < text2.size(); ++index2)
            {
                if (text1[index1] == text2[index2])
                    nextRow[index2] = 1 + (index1 == 0 || index2 == 0 ? 0 : currentRow[index2 - 1]);
                else
                    nextRow[index2] = std::max(currentRow[index2], index2 == 0 ? 0 : nextRow[index2 - 1]);
            }
            std::swap(currentRow, nextRow);
        }
        return static_cast<int>(currentRow.back());
    }
};

}

namespace LongestCommonSubsequenceTask
{

TEST(LongestCommonSubsequenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.longestCommonSubsequence("abcde", "ace"));
    ASSERT_EQ(3, solution.longestCommonSubsequence("abc", "abc"));
    ASSERT_EQ(0, solution.longestCommonSubsequence("abc", "def"));
}

}