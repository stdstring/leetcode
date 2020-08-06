#include <cctype>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string licenseKeyFormatting(std::string const &S, int K) const
    {
        int groupRest = K;
        std::string buffer;
        for (std::string::const_reverse_iterator it = S.crbegin(); it != S.crend(); ++it)
        {
            const char ch = *it;
            if (ch == '-')
                continue;
            if (groupRest == 0)
            {
                buffer.push_back('-');
                groupRest = K;
            }
            buffer.push_back(std::toupper(ch));
            --groupRest;
        }
        return {buffer.rbegin(), buffer.rend()};
    }
};

}

namespace LicenseKeyFormattingTask
{

TEST(LicenseKeyFormattingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("5F3Z-2E9W", solution.licenseKeyFormatting("5F3Z-2e-9-w", 4));
    ASSERT_EQ("2-5G-3J", solution.licenseKeyFormatting("2-5g-3-J", 2));
}

TEST(LicenseKeyFormattingTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("AA-AA", solution.licenseKeyFormatting("--a-a-a-a--", 2));
}

}