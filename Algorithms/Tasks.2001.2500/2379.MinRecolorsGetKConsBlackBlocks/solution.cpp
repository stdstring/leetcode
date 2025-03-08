#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumRecolors(std::string const &blocks, int k) const
    {
        const size_t windowSize = k;
        int currentWhiteCount = 0;
        // init
        for (size_t index = 0; index < windowSize; ++index)
            currentWhiteCount += (blocks[index] == 'W' ? 1 : 0);
        int minWhiteCount = currentWhiteCount;
        // move
        for (size_t index = windowSize; index < blocks.size(); ++index)
        {
            currentWhiteCount -= (blocks[index - windowSize] == 'W' ? 1 : 0);
            currentWhiteCount += (blocks[index] == 'W' ? 1 : 0);
            minWhiteCount = std::min(minWhiteCount, currentWhiteCount);
        }
        return minWhiteCount;
    }
};

}

namespace MinRecolorsGetKConsBlackBlocksTask
{

TEST(MinRecolorsGetKConsBlackBlocksTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumRecolors("WBBWWBBWBW", 7));
    ASSERT_EQ(0, solution.minimumRecolors("WBWBBBW", 2));
}

}