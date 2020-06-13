#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string addBinary(std::string const &a, std::string const &b) const
    {
        std::string buf;
        size_t maxSize = std::max(a.size(), b.size());
        std::div_t dv{};
        char carry = 0;
        for (size_t index = 0; index < maxSize; ++index)
        {
            char aDigit = (index < a.size()) ? a[a.size() - index - 1] - '0' : 0;
            char bDigit = (index < b.size()) ? b[b.size() - index - 1] - '0' : 0;
            char sum = aDigit + bDigit + carry;
            dv.quot = sum;
            dv = std::div(dv.quot, 2);
            buf += "01"[dv.rem];
            carry = dv.quot;
        }
        if (carry == 1) buf += "1";
        return {buf.rbegin(), buf.rend()};
    }
};

}

namespace AddBinaryTask
{

TEST(AddBinaryTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("100", solution.addBinary("11", "1"));
    ASSERT_EQ("10101", solution.addBinary("1010", "1011"));
}

TEST(AddBinaryTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("1", solution.addBinary("0", "1"));
    ASSERT_EQ("1000", solution.addBinary("1", "111"));
}

}