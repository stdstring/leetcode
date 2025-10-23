#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool hasSameDigits(std::string const &s) const
    {
        std::string result(s);
        while (result.size() > 2)
        {
            std::string current(result.size() - 1, ' ');
            for (size_t index = 0; index < result.size() -1; ++index)
            {
                constexpr int digitStart = '0';
                constexpr int digitsCount = 10;
                const int digitSum = ((result[index] - digitStart) + (result[index + 1] - digitStart)) % digitsCount;
                const char digit = static_cast<char>(digitStart + digitSum);
                current[index] = digit;
            }
            std::swap(result, current);
        }
        return result[0] == result[1];
    }
};

}

namespace CheckIfDigitsEqualInStringAfterOps1Task
{

TEST(CheckIfDigitsEqualInStringAfterOps1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.hasSameDigits("3902"));
    ASSERT_EQ(false, solution.hasSameDigits("34789"));
}

}