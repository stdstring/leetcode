#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string restoreString(std::string const &s, std::vector<int> const &indices) const
    {
        std::string dest(s.size(), ' ');
        for (size_t index = 0; index < indices.size(); ++index)
            dest[indices[index]] = s[index];
        return dest;
    }
};

}

namespace ShuffleStringTask
{

TEST(ShuffleStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("leetcode", solution.restoreString("codeleet", {4, 5, 6, 7, 0, 2, 1, 3}));
    ASSERT_EQ("abc", solution.restoreString("abc", {0, 1, 2}));
    ASSERT_EQ("nihao", solution.restoreString("aiohn", {3, 1, 4, 2, 0}));
    ASSERT_EQ("arigatou", solution.restoreString("aaiougrt", {4, 0, 2, 6, 7, 3, 1, 5}));
    ASSERT_EQ("rat", solution.restoreString("art", {1, 0, 2}));
}

}