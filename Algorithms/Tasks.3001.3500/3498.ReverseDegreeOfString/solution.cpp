#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int reverseDegree(std::string const &s) const
    {
        int result = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            constexpr size_t alphabetSize = 26;
            constexpr size_t alphabetStart = 'a';
            const int position = static_cast<int>(index + 1);
            const int reversedChar = static_cast<int>(alphabetSize - (s[index] - alphabetStart));
            result += position * reversedChar;
        }
        return result;
    }
};

}

namespace ReverseDegreeOfStringTask
{

TEST(ReverseDegreeOfStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(148, solution.reverseDegree("abc"));
    ASSERT_EQ(160, solution.reverseDegree("zaza"));
}

}