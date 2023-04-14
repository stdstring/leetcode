#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestPalindromeSubseq(std::string const &s) const
    {
        std::vector<int> prevRow(s.size(), 0);
        for (size_t row = 0; row < s.size(); ++row)
        {
            std::vector<int> currentRow(s.size(), 0);
            for (size_t column = 0; column < s.size(); ++column)
            {
                const size_t reversedColumn = s.size() - 1 - column;
                if (s[row] == s[reversedColumn])
                    currentRow[column] = 1 + (column > 0 ? prevRow[column - 1] : 0);
                else
                    currentRow[column] = std::max(column > 0 ? currentRow[column - 1] : 0, prevRow[column]);
            }
            std::swap(prevRow, currentRow);
        }
        return prevRow.back();
    }
};

}

namespace LongestPalindromicSubsequenceTask
{

TEST(LongestPalindromicSubsequenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.longestPalindromeSubseq("bbbab"));
    ASSERT_EQ(2, solution.longestPalindromeSubseq("cbbd"));
}

}