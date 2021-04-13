#include <algorithm>
#include <iterator>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string reformatNumber(std::string const &number) const
    {
        std::string digits;
        std::copy_if(number.cbegin(), number.cend(), std::back_inserter(digits), [](char ch){ return std::isdigit(ch); });
        std::string result;
        size_t rest = digits.size() % 3 == 1 ? 4 : digits.size() % 3;
        for (size_t index = 0; index < digits.size() - rest; ++index)
            appendDigit(result, digits[index], index);
        if (rest == 4)
        {
            appendDash(result);
            result.append(digits.substr(digits.size() - 4, 2));
            rest -= 2;
        }
        if (rest == 2)
        {
            appendDash(result);
            result.append(digits.substr(digits.size() - 2));
        }
        return result;
    }

private:
    void appendDash(std::string &dest) const
    {
        if (!dest.empty())
            dest.push_back('-');
    }

    void appendDigit(std::string &dest, char digit, size_t index) const
    {
        if (index % 3 == 0)
            appendDash(dest);
        dest.push_back(digit);
    }
};

}

namespace ReformatPhoneNumberTask
{

TEST(ReformatPhoneNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("123-456", solution.reformatNumber("1-23-45 6"));
    ASSERT_EQ("123-45-67", solution.reformatNumber("123 4-567"));
    ASSERT_EQ("123-456-78", solution.reformatNumber("123 4-5678"));
    ASSERT_EQ("12", solution.reformatNumber("12"));
    ASSERT_EQ("175-229-353-94-75", solution.reformatNumber("--17-5 229 35-39475 "));
}

}