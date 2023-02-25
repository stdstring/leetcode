#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countBinarySubstrings(std::string const &s) const
    {
        size_t substringsCount = 0;
        char currentGroupLeader = s.front();
        size_t currentGroupSize = 0;
        size_t prevGroupSize = 0;
        for (char ch : s)
        {
            if (ch == currentGroupLeader)
                ++currentGroupSize;
            else
            {
                substringsCount += std::min(currentGroupSize, prevGroupSize);
                prevGroupSize = currentGroupSize;
                currentGroupSize = 1;
                currentGroupLeader = ch;
            }
        }
        return static_cast<int>(substringsCount + std::min(currentGroupSize, prevGroupSize));
    }
};

}

namespace CountBinarySubstringsTask
{

TEST(CountBinarySubstringsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.countBinarySubstrings("00110011"));
    ASSERT_EQ(4, solution.countBinarySubstrings("10101"));
}

}