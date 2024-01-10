#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumLength(std::string const &s) const
    {
        size_t maxSize = s.size();
        size_t firstStart = 0;
        bool skip = false;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if ((s[index] == s[firstStart]) && skip)
                continue;
            if (s[index] != s[firstStart])
            {
                firstStart = index;
                skip = false;
            }
            const size_t substringSize = index - firstStart + 1;
            std::string substring(substringSize, s[index]);
            const size_t secondStart = s.find(substring, firstStart + 1);
            if (secondStart == std::string::npos)
            {
                skip = true;
                continue;
            }
            const size_t thirdStart = s.find(substring, secondStart + 1);
            if (thirdStart == std::string::npos)
            {
                skip = true;
                continue;
            }
            maxSize = std::max(substringSize, maxSize == s.size() ? 0 : maxSize);
        }
        if (maxSize == s.size())
            return -1;
        return static_cast<int>(maxSize);
    }
};

}

namespace FindLongestSpecialSubstrOccursThrice1Task
{

TEST(FindLongestSpecialSubstrOccursThrice1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maximumLength("aaaa"));
    ASSERT_EQ(-1, solution.maximumLength("abcdef"));
    ASSERT_EQ(1, solution.maximumLength("abcaba"));
}

TEST(FindLongestSpecialSubstrOccursThrice1TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maximumLength("aaaaabaaaa"));
}

TEST(FindLongestSpecialSubstrOccursThrice1TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(-1, solution.maximumLength("cbc"));
}

}