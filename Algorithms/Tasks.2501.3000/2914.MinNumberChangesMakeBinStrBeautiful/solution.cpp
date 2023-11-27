#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minChanges(std::string const &s) const
    {
        int changesCount = 0;
        for (size_t index = 0; index < s.size(); index += 2)
        {
            if (s[index] != s[index + 1])
                ++changesCount;
        }
        return changesCount;
    }
};

}

namespace MinNumberChangesMakeBinStrBeautifulTask
{

TEST(MinNumberChangesMakeBinStrBeautifulTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minChanges("1001"));
    ASSERT_EQ(1, solution.minChanges("10"));
    ASSERT_EQ(0, solution.minChanges("0000"));
}

}