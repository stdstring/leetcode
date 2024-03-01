#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string maximumOddBinaryNumber(std::string const &s) const
    {
        const size_t oneCount = std::ranges::count(s, '1');
        const size_t zeroCount = s.size() - oneCount;
        return std::string(oneCount - 1, '1') + std::string(zeroCount, '0') + "1";
    }
};

}

namespace MaxOddBinaryNumberTask
{

TEST(MaxOddBinaryNumberTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("001", solution.maximumOddBinaryNumber("010"));
    ASSERT_EQ("1001", solution.maximumOddBinaryNumber("0101"));
}

}