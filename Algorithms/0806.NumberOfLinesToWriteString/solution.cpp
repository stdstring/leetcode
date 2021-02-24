#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> numberOfLines(std::vector<int> const &widths, std::string const &s) const
    {
        constexpr int maxWidth = 100;
        constexpr size_t firstChar = 'a';
        int linesCount = 1;
        int lastLineWidth = 0;
        for (char ch : s)
        {
            lastLineWidth += widths[ch - firstChar];
            if (lastLineWidth > maxWidth)
            {
                ++linesCount;
                lastLineWidth = widths[ch - firstChar];
            }
        }
        return {linesCount, lastLineWidth};
    }
};

}

namespace NumberOfLinesToWriteStringTask
{

TEST(NumberOfLinesToWriteStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({3, 60}), solution.numberOfLines({10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, "abcdefghijklmnopqrstuvwxyz"));
    ASSERT_EQ(std::vector<int>({2, 4}), solution.numberOfLines({4, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, "bbbcccdddaaa"));
}

}