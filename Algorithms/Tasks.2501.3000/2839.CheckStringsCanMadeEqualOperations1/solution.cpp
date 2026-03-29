#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canBeEqual(std::string const &s1, std::string const &s2) const
    {
        std::string result(s1);
        // case 0
        if (result == s2)
            return true;
        // case 1
        std::swap(result[0], result[2]);
        if (result == s2)
            return true;
        // case 2
        std::swap(result[0], result[2]);
        std::swap(result[1], result[3]);
        if (result == s2)
            return true;
        // case 3
        std::swap(result[0], result[2]);
        if (result == s2)
            return true;
        return false;
    }
};

}

namespace CheckStringsCanMadeEqualOperations1Task
{

TEST(CheckStringsCanMadeEqualOperations1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canBeEqual("abcd", "cdab"));
    ASSERT_EQ(false, solution.canBeEqual("abcd", "dacb"));
}

}