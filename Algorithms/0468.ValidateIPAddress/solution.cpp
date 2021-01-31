#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string validIPAddress(std::string const &ip) const
    {
        if (ip.find(IP4Delimiter) != std::string::npos)
            return checkIP4(ip) ? "IPv4" : "Neither";
        if (ip.find(IP6Delimiter) != std::string::npos)
            return checkIP6(ip) ? "IPv6" : "Neither";
        return "Neither";
    }

private:
    static constexpr char IP4Delimiter = '.';
    static constexpr char IP6Delimiter = ':';

    bool checkIP4(std::string const &source) const
    {

        size_t index = 0;
        // x1.x2.x3.x4
        for (size_t part = 1; part <= 4; ++part)
        {
            if ((part > 1) && !checkDelimiter(source, index, IP4Delimiter))
                return false;
            if (!checkIP4Part(source, index))
                return false;
        }
        return index == source.size();
    }

    bool checkIP6(std::string const &source) const
    {
        size_t index = 0;
        // x1:x2:x3:x4:x5:x6:x7:x8
        for (size_t part = 1; part <= 8; ++part)
        {
            if ((part > 1) && !checkDelimiter(source, index, IP6Delimiter))
                return false;
            if (!checkIP6Part(source, index))
                return false;
        }
        return index == source.size();
    }

    bool checkDelimiter(std::string const &source, size_t &index, char delimiter) const
    {
        if (index == source.size() || source[index] != delimiter)
            return false;
        ++index;
        return true;
    }

    bool checkIP4Part(std::string const &source, size_t &index) const
    {
        constexpr int partMaxValue = 255;
        constexpr size_t partMaxSize = 3;
        const size_t start = index;
        int number = 0;
        while (index < source.size() && source[index] != IP4Delimiter && source[index] != IP6Delimiter)
        {
            if ((index - start) == partMaxSize)
                return false;
            if (!std::isdigit(source[index]))
                return false;
            number = 10 * number + (source[index++] - '0');
        }
        return (index > start) && ((index - start) == 1 || source[start] != '0') && number <= partMaxValue;
    }

    bool checkIP6Part(std::string const &source, size_t &index) const
    {
        constexpr size_t partMaxSize = 4;
        const size_t start = index;
        while (index < source.size() && source[index] != IP4Delimiter && source[index] != IP6Delimiter)
        {
            if ((index - start) == partMaxSize)
                return false;
            if (!std::isxdigit(source[index]))
                return false;
            ++index;
        }
        return (index > start);
    }
};

}

namespace ValidateIPAddressTask
{

TEST(ValidateIPAddressTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("IPv4", solution.validIPAddress("172.16.254.1"));
    ASSERT_EQ("IPv6", solution.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334"));
    ASSERT_EQ("Neither", solution.validIPAddress("256.256.256.256"));
    ASSERT_EQ("Neither", solution.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334:"));
    ASSERT_EQ("Neither", solution.validIPAddress("1e1.4.5.6"));
    ASSERT_EQ("IPv4", solution.validIPAddress("192.168.1.1"));
    ASSERT_EQ("IPv4", solution.validIPAddress("192.168.1.0"));
    ASSERT_EQ("Neither", solution.validIPAddress("192.168.01.1"));
    ASSERT_EQ("Neither", solution.validIPAddress("192.168.1.00"));
    ASSERT_EQ("Neither", solution.validIPAddress("192.168@1.1"));
    ASSERT_EQ("IPv6", solution.validIPAddress("2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    ASSERT_EQ("Neither", solution.validIPAddress("2001:0db8:85a3::8A2E:037j:7334"));
    ASSERT_EQ("Neither", solution.validIPAddress("02001:0db8:85a3:0000:0000:8a2e:0370:7334"));
}

TEST(ValidateIPAddressTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("Neither", solution.validIPAddress("111111111111.111111111111.111111111111.111111111111"));
}

}
