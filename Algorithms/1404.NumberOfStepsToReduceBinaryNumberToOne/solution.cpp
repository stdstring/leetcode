#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSteps(std::string const &s) const
    {
        std::string revBits(s.crbegin(), s.crend());
        size_t count = 0;
        for (size_t index = 0; index < revBits.size() - 1; ++index)
        {
            if (revBits[index] == '1')
            {
                increase(revBits, index);
                ++count;
            }
            ++count;
        }
        return static_cast<int>(count);
    }

private:
    void increase(std::string &revBits, size_t current) const
    {
        for (size_t index = current; index < revBits.size(); ++index)
        {
            if (revBits[index] == '0')
            {
                revBits[index] = '1';
                return;
            }
            revBits[index] = '0';
        }
        revBits.push_back('1');
    }
};

}

namespace NumberOfStepsToReduceBinaryNumberToOneTask
{

TEST(NumberOfStepsToReduceBinaryNumberToOneTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.numSteps("1101"));
    ASSERT_EQ(1, solution.numSteps("10"));
    ASSERT_EQ(0, solution.numSteps("1"));
}

}