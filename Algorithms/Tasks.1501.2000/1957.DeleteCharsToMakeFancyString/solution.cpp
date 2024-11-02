#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string makeFancyString(std::string const &s) const
    {
        std::string result;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (index < 2)
                result.push_back(s[index]);
            else
            {
                size_t resultIndex = result.size() - 1;
                if ((s[index] != result[resultIndex]) || (s[index] != result[resultIndex - 1]))
                    result.push_back(s[index]);
            }
        }
        return result;
    }
};

}

namespace DeleteCharsToMakeFancyStringTask
{

TEST(DeleteCharsToMakeFancyStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("leetcode", solution.makeFancyString("leeetcode"));
    ASSERT_EQ("aabaa", solution.makeFancyString("aaabaaaa"));
    ASSERT_EQ("aab", solution.makeFancyString("aab"));
}

}