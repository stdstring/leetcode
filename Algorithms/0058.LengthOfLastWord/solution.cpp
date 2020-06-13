#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int lengthOfLastWord(std::string const &s) const
    {
        if (s.empty())
            return 0;
        int backIndex = s.size() - 1;
        // skip last spaces
        while ((backIndex >= 0) && (s[backIndex] == ' '))
            --backIndex;
        // find last word
        int frontIndex = backIndex;
        while ((frontIndex >= 0) && (s[frontIndex] != ' '))
            --frontIndex;
        return backIndex - frontIndex;
    }
};

}

namespace LengthOfLastWordTask
{

TEST(LengthOfLastWordTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.lengthOfLastWord("Hello World"));
}

}