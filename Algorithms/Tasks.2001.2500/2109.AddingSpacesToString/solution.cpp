#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string addSpaces(std::string const &s, std::vector<int> const &spaces) const
    {
        std::string dest;
        size_t index = 0;
        for (const int space : spaces)
        {
            dest.append(s.substr(index, space - index)).append(1, ' ');
            index = space;
        }
        dest.append(s.substr(index));
        return dest;
    }
};

}

namespace AddingSpacesToStringTask
{

TEST(AddingSpacesToStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("Leetcode Helps Me Learn", solution.addSpaces("LeetcodeHelpsMeLearn", {8, 13, 15}));
    ASSERT_EQ("i code in py thon", solution.addSpaces("icodeinpython", {1, 5, 7, 9}));
    ASSERT_EQ(" s p a c i n g", solution.addSpaces("spacing", {0, 1, 2, 3, 4, 5, 6}));
}

}