#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minFlipsMonoIncr(std::string const &s) const
    {
        size_t flip0Count = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] == '1')
                ++flip0Count;
        }
        size_t minFlipCount = flip0Count;
        size_t flip1Count = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            flip0Count -= (s[s.size() - 1 - index] == '1' ? 1 : 0);
            flip1Count += (s[s.size() - 1 - index] == '0' ? 1 : 0);
            minFlipCount = std::min(minFlipCount, flip0Count + flip1Count);
        }
        return static_cast<int>(minFlipCount);
    }
};

}

namespace FlipStringToMonotoneIncreasingTask
{

TEST(FlipStringToMonotoneIncreasingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.minFlipsMonoIncr("00110"));
    ASSERT_EQ(2, solution.minFlipsMonoIncr("010110"));
    ASSERT_EQ(2, solution.minFlipsMonoIncr("00011000"));
}

}