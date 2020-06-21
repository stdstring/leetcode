#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string toHex(int num) const
    {
        if (num == 0)
            return "0";
        unsigned int number = static_cast<unsigned int>(num);
        std::string buffer;
        while (number > 0)
        {
            const unsigned int digit = number & 0xf;
            number >>= 4;
            buffer.push_back(digit < 10 ? '0' + digit : 'a' + digit - 10);
        }
        return {buffer.rbegin(), buffer.rend()};
    }
};

}

namespace ConvertNumberToHexadecimalTask
{

TEST(ConvertNumberToHexadecimalTask, Examples)
{
    const Solution solution;
    ASSERT_EQ("1a", solution.toHex(26));
    ASSERT_EQ("ffffffff", solution.toHex(-1));
}

}