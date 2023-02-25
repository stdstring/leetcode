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
        size_t backIndex = s.size() - 1;
        // skip last spaces
        while ((backIndex >= 0) && (s[backIndex] == ' '))
            --backIndex;
        // find last word
        size_t frontIndex = backIndex;
        while ((frontIndex >= 0) && (s[frontIndex] != ' '))
            --frontIndex;
        return static_cast<int>(backIndex - frontIndex);
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