#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string largestOddNumber(std::string const &num) const
    {
        for (size_t rIndex = 0; rIndex < num.size(); ++rIndex)
        {
            const size_t index = num.size() - 1 - rIndex;
            const int digit = num[index] - '0';
            if ((digit % 2) == 1)
                return num.substr(0, index + 1);
        }
        return "";
    }
};

}

namespace LargestOddNumberInStringTask
{

TEST(LargestOddNumberInStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("5", solution.largestOddNumber("52"));
    ASSERT_EQ("", solution.largestOddNumber("4206"));
    ASSERT_EQ("35427", solution.largestOddNumber("35427"));
}

}