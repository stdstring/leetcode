#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string toLowerCase(std::string const &str) const
    {
        std::string dest(str.size(), ' ');
        for (size_t index = 0; index < str.size(); ++index)
            dest[index] = ('A' <= str[index] && str[index] <= 'Z') ? 'a' + (str[index] - 'A') : str[index];
        return dest;
    }
};

}

namespace ToLowerCaseTask
{

TEST(ToLowerCaseTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("hello", solution.toLowerCase("Hello"));
    ASSERT_EQ("here", solution.toLowerCase("here"));
    ASSERT_EQ("lovely", solution.toLowerCase("LOVELY"));
}

}