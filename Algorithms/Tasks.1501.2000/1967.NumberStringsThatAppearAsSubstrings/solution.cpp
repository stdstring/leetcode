#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numOfStrings(std::vector<std::string> const &patterns, std::string const &word) const
    {
        size_t result = 0;
        for (std::string const &pattern : patterns)
        {
            if (word.contains(pattern))
                ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace NumberStringsThatAppearAsSubstringsTask
{

TEST(NumberStringsThatAppearAsSubstringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numOfStrings({"a", "abc", "bc", "d"}, "abc"));
    ASSERT_EQ(2, solution.numOfStrings({"a", "b", "c"}, "aaaaabbbbb"));
    ASSERT_EQ(3, solution.numOfStrings({"a", "a", "a"}, "ab"));
}

}