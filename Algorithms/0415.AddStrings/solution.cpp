#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string addStrings(std::string const &a, std::string const &b) const
    {
        std::string buf;
        const size_t maxSize = std::max(a.size(), b.size());
        std::div_t dv;
        char carry = 0;
        for (size_t index = 0; index < maxSize; ++index)
        {
            const char aDigit = (index < a.size()) ? a[a.size() - index - 1] - '0' : 0;
            const char bDigit = (index < b.size()) ? b[b.size() - index - 1] - '0' : 0;
            const char sum = aDigit + bDigit + carry;
            dv.quot = sum;
            dv = std::div(dv.quot, 10);
            buf += "0123456789"[dv.rem];
            carry = dv.quot;
        }
        if (carry == 1)
            buf += "1";
        return {buf.rbegin(), buf.rend()};
    }
};

}

namespace AddStringsTask
{

TEST(AddStringsTaskTests, CustomExamples)
{
    const Solution solution;
    ASSERT_EQ("31", solution.addStrings("13", "18"));
    ASSERT_EQ("197", solution.addStrings("99", "98"));
}

}