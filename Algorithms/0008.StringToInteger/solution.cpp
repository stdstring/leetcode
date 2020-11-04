#include <limits>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int myAtoi(std::string const &str) const
    {
        std::string::const_iterator iterator = str.cbegin();
        // skip leading whitespaces
        while (iterator != str.cend() && *iterator == ' ')
            ++iterator;
        if (iterator == str.cend())
            return 0;
        bool positive = true;
        // process optional sign
        if (*iterator == '+' || *iterator == '-')
        {
            positive = *iterator == '+';
            ++iterator;
        }
        long long result = 0;
        // process digits
        while (iterator != str.cend() && *iterator >= '0' && *iterator <= '9')
        {
            result = 10 * result + (*iterator - '0');
            if (positive && result > std::numeric_limits<int>::max())
                return std::numeric_limits<int>::max();
            if (!positive && (-result) < std::numeric_limits<int>::min())
                return std::numeric_limits<int>::min();
            ++iterator;
        }
        return static_cast<int>(positive ? result : -result);
    }
};

}

namespace StringToIntegerTask
{

TEST(StringToIntegerTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(42, solution.myAtoi("42"));
    ASSERT_EQ(-42, solution.myAtoi("   -42"));
    ASSERT_EQ(4193, solution.myAtoi("4193 with words"));
    ASSERT_EQ(0, solution.myAtoi("words and 987"));
    ASSERT_EQ(INT_MIN, solution.myAtoi("-91283472332"));
}

}