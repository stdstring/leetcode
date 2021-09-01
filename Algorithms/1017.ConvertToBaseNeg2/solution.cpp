#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string baseNeg2(int n) const
    {
        if (n == 0)
            return "0";
        constexpr int base = -2;
        std::string result;
        while (n != 0)
        {
            int rem = n % base;
            if (rem < 0)
                rem -= base;
            result.push_back(static_cast<char>('0' + rem));
            n = (n - rem) / base;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

}

namespace ConvertToBaseNeg2Task
{

TEST(ConvertToBaseNeg2TaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("110", solution.baseNeg2(2));
    ASSERT_EQ("111", solution.baseNeg2(3));
    ASSERT_EQ("100", solution.baseNeg2(4));
}

TEST(ConvertToBaseNeg2TaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("0", solution.baseNeg2(0));
}

}