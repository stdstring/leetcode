#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumDeletions(std::string const &s) const
    {
        size_t deleteB = std::ranges::count(s, 'b');
        size_t deleteA = 0;
        size_t minDelete = deleteB;
        for (size_t rIndex = 0; rIndex < s.size(); ++rIndex)
        {
            const size_t index = s.size() - 1 - rIndex;
            deleteA += (s[index] == 'a' ? 1 : 0);
            deleteB -= (s[index] == 'b' ? 1 : 0);
            minDelete = std::min(minDelete, deleteA + deleteB);
        }
        return static_cast<int>(minDelete);
    }
};

}

namespace MinDeletionsMakeStringBalancedTask
{

TEST(MinDeletionsMakeStringBalancedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumDeletions("aababbab"));
    ASSERT_EQ(2, solution.minimumDeletions("bbaaaaabb"));
}

}