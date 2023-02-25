#include <string>
#include <stdexcept>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minAddToMakeValid(std::string const &s) const
    {
        int minAdd = 0;
        int balance = 0;
        for (const char ch : s)
        {
            switch(ch)
            {
                case '(':
                    ++balance;
                    break;
                case ')':
                    if (balance > 0)
                        --balance;
                    else
                        ++minAdd;
                    break;
                default:
                    throw std::logic_error("Bad character");
            }
        }
        return minAdd + balance;
    }
};

}

namespace MinAddToMakeParenthesesValidTask
{

TEST(MinAddToMakeParenthesesValidTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.minAddToMakeValid("())"));
    ASSERT_EQ(3, solution.minAddToMakeValid("((("));
}

}