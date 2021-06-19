#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string maskPII(std::string const &s) const
    {
        const size_t atPosition = s.find('@');
        return atPosition == std::string::npos ? maskPhone(s) : maskEmail(s, atPosition);
    }

private:
    std::string maskEmail(std::string const &source, size_t atPosition) const
    {
        std::string dest;
        dest.push_back(static_cast<char>(std::tolower(source[0])));
        dest.append("*****");
        dest.push_back(static_cast<char>(std::tolower(source[atPosition - 1])));
        std::transform(source.cbegin() + atPosition, source.cend(), std::back_inserter(dest), [](char ch){ return  std::tolower(ch); });
        return dest;
    }

    std::string maskPhone(std::string const &source) const
    {
        const size_t digitsCount = std::count_if(source.cbegin(), source.cend(), [](char ch){ return std::isdigit(ch) != 0; });
        std::string dest;
        constexpr size_t localNumberSize = 10;
        size_t pos = 0;
        if (digitsCount > localNumberSize)
        {
            dest.push_back('+');
            fillDigitsGroup(source, pos, digitsCount - localNumberSize, dest, [](char _){ return '*'; });
            dest.push_back('-');
        }
        fillDigitsGroup(source, pos, 3, dest, [](char _){ return '*'; });
        dest.push_back('-');
        fillDigitsGroup(source, pos, 3, dest, [](char _){ return '*'; });
        dest.push_back('-');
        fillDigitsGroup(source, pos, 4, dest, [](char ch){ return ch; });
        return dest;
    }

    void fillDigitsGroup(std::string const &source, size_t &pos, size_t expectedSize, std::string &dest, std::function<char(char)> const &maskFunc) const
    {
        const size_t sizeBefore = dest.size();
        while (dest.size() < sizeBefore + expectedSize)
        {
            if (std::isdigit(source[pos]))
                dest.push_back(maskFunc(source[pos]));
            ++pos;
        }
    }
};

}

namespace MaskingPersonalInformationTask
{

TEST(MaskingPersonalInformationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("l*****e@leetcode.com", solution.maskPII("LeetCode@LeetCode.com"));
    ASSERT_EQ("a*****b@qq.com", solution.maskPII("AB@qq.com"));
    ASSERT_EQ("***-***-7890", solution.maskPII("1(234)567-890"));
    ASSERT_EQ("+**-***-***-5678", solution.maskPII("86-(10)12345678"));
}

}