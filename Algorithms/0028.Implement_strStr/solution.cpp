#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int strStr(std::string const &haystack, std::string const &needle) const
    {
        if (needle.empty())
            return 0;
        if (haystack.size() < needle.size())
            return -1;
        for (size_t i = 0; i <= (haystack.size() - needle.size()); ++i)
        {
            bool isMatch = true;
            for (size_t j = 0; j < needle.size(); ++j)
            {
                if (haystack[i + j] != needle[j])
                {
                    isMatch = false;
                    break;
                }
            }
            if (isMatch)
                return static_cast<int>(i);
        }
        return -1;
    }
};

}

namespace Implement_strStrTask
{

    TEST(Implement_strStrTaskTests, Examples)
    {
        const Solution solution;
        ASSERT_EQ(2, solution.strStr("hello", "ll"));
        ASSERT_EQ(-1, solution.strStr("aaaaa", "bba"));
    }

    TEST(Implement_strStrTaskTests, FromWrongAnswers)
    {
        const Solution solution;
        ASSERT_EQ(-1, solution.strStr("", "a"));
    }

}