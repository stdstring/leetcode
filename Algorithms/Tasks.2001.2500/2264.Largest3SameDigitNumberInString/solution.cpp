#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string largestGoodInteger(std::string const &num) const
    {
        std::string bestValue;
        for (size_t index = 0; index < num.size() - 2; ++index)
        {
            if ((num[index] != num[index + 1]) || (num[index] != num[index + 2]))
                continue;
            if (bestValue.empty() || (bestValue[0] < num[index]))
                bestValue = std::string(3, num[index]);
        }
        return bestValue;
    }
};

}

namespace Largest3SameDigitNumberInStringTask
{

TEST(Largest3SameDigitNumberInStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("777", solution.largestGoodInteger("6777133339"));
    ASSERT_EQ("000", solution.largestGoodInteger("2300019"));
    ASSERT_EQ("", solution.largestGoodInteger("42352338"));
}

}