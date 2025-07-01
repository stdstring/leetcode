#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int possibleStringCount(std::string const &word) const
    {
        size_t possibleCount = 1;
        for (size_t index = 1; index < word.size(); ++index)
        {
            if (word[index] == word[index - 1])
                ++possibleCount;
        }
        return static_cast<int>(possibleCount);
    }
};

}

namespace FindOriginalTypedString1Task
{

TEST(FindOriginalTypedString1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.possibleStringCount("abbcccc"));
    ASSERT_EQ(1, solution.possibleStringCount("abcd"));
    ASSERT_EQ(4, solution.possibleStringCount("aaaa"));
}

}