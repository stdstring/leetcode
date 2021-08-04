#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string defangIPaddr(std::string const &address) const
    {
        std::string result;
        for (char ch : address)
        {
            if (ch == '.')
                result.append("[.]");
            else
                result.push_back(ch);
        }
        return result;
    }
};

}

namespace DefangingIPAddressTask
{

TEST(DefangingIPAddressTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("1[.]1[.]1[.]1", solution.defangIPaddr("1.1.1.1"));
    ASSERT_EQ("255[.]100[.]50[.]0", solution.defangIPaddr("255.100.50.0"));
}

}