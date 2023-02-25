#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool queryString(std::string const &s, int n) const
    {
        std::string source(s.crbegin(), s.crend());
        for (int number = 1; number <= n; ++number)
        {
            if (source.find(toBinaryString(number)) == std::string::npos)
                return false;
        }
        return true;
    }

private:
    [[nodiscard]] std::string toBinaryString(int number) const
    {
        std::string result;
        while (number != 0)
        {
            result.push_back((number & 1) == 1 ? '1' : '0');
            number >>= 1;
        }
        return result;
    }
};

}

namespace BinaryStringWithSubstrings1ToNTask
{

TEST(BinaryStringWithSubstrings1ToNTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.queryString("0110", 3));
    ASSERT_EQ(false, solution.queryString("0110", 4));
}

}