#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countSubstrings(std::string const &s, char c) const
    {
        const long long count = std::ranges::count(s, c);
        return count * (1 + count) / 2;
    }
};

}

namespace CountSubstrStartEndWithGivenCharTask
{

TEST(CountSubstrStartEndWithGivenCharTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.countSubstrings("abada", 'a'));
    ASSERT_EQ(6, solution.countSubstrings("zzz", 'z'));
}

}