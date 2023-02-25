#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int secondHighest(std::string const &s) const
    {
        int largestDigit = -1;
        int secondLargestDigit = -1;
        for (char ch : s)
        {
            if (std::isdigit(ch))
            {
                const int digit = ch - '0';
                if (digit > largestDigit)
                {
                    secondLargestDigit = largestDigit;
                    largestDigit = digit;
                }
                else if ((digit < largestDigit) && (digit > secondLargestDigit))
                    secondLargestDigit = digit;
            }
        }
        return secondLargestDigit;
    }
};

}

namespace SecondLargestDigitInStringTask
{

TEST(SecondLargestDigitInStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.secondHighest("dfa12321afd"));
    ASSERT_EQ(-1, solution.secondHighest("abc1111"));
}

}