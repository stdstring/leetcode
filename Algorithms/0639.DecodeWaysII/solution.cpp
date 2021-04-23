#include <cstdint>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numDecodings(std::string const &s) const
    {
        const uint64_t modValue = 1000000007;
        std::vector<int> decodeWaysCount(s.size() + 1, 0);
        decodeWaysCount[0] = 1;
        for (size_t index = 0; index < decodeWaysCount.size() - 1; ++index)
        {
            const uint64_t waysCount = decodeWaysCount[index];
            decodeWaysCount[index + 1] = (waysCount * calcSingleNumberCases(s, index) + decodeWaysCount[index + 1]) % modValue;
            if (index < (decodeWaysCount.size() - 2))
                decodeWaysCount[index + 2] = (waysCount * calcDoubleNumberCases(s, index) + decodeWaysCount[index + 2]) % modValue;
        }
        return decodeWaysCount.back();
    }

private:
    int calcSingleNumberCases(std::string const &s, size_t index) const
    {
        if (s[index] == '0')
            return 0;
        if (s[index] == '*')
            return 9;
        return 1;
    }

    int calcDoubleNumberCases(std::string const &s, size_t index) const
    {
        switch (s[index])
        {
            case '0':
                return 0;
            case '1':
                return s[index + 1] == '*' ? 9 : 1;
            case '2':
                if (s[index + 1] == '*')
                    return 6;
                if (('0' <= s[index + 1]) && (s[index + 1] <= '6'))
                    return 1;
                return 0;
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return 0;
            case '*':
                if (s[index + 1] == '*')
                    return 15;
                if (('0' <= s[index + 1]) && (s[index + 1] <= '6'))
                    return 2;
                return 1;
            default:
                return 0;
        }
    }
};

}

namespace DecodeWaysIITask
{

TEST(DecodeWaysIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(9, solution.numDecodings("*"));
    ASSERT_EQ(18, solution.numDecodings("1*"));
    ASSERT_EQ(15, solution.numDecodings("2*"));
}

TEST(DecodeWaysIITaskTests, CustomExamples)
{
    const Solution solution;
    ASSERT_EQ(288, solution.numDecodings("1*2*"));
    ASSERT_EQ(114, solution.numDecodings("**6"));
}

}