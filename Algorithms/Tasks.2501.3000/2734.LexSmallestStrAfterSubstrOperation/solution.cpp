#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string smallestString(std::string const &s) const
    {
        std::string result(s);
        size_t start = 0;
        while ((start < result.size()) && result[start] == 'a')
            ++start;
        if (start == result.size())
            result.back() = 'z';
        else
        {
            for (size_t index = start; (index < result.size()) && (result[index] != 'a'); ++index)
                --result[index];
        }
        return result;
    }
};

}

namespace LexSmallestStrAfterSubstrOperationTask
{

TEST(LexSmallestStrAfterSubstrOperationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("baabc", solution.smallestString("cbabc"));
    ASSERT_EQ("abaab", solution.smallestString("acbbc"));
    ASSERT_EQ("kddsbncd", solution.smallestString("leetcode"));
}

TEST(LexSmallestStrAfterSubstrOperationTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ("aaz", solution.smallestString("aaa"));
}

}