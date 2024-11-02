#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isCircularSentence(std::string const &sentence) const
    {
        for (size_t spacePos = sentence.find(' '); spacePos != std::string::npos; spacePos = sentence.find(' ', spacePos + 1))
        {
            if (sentence[spacePos - 1] != sentence[spacePos + 1])
                return false;
        }
        return sentence.front() == sentence.back();
    }
};

}

namespace CircularSentenceTask
{

TEST(CircularSentenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isCircularSentence("leetcode exercises sound delightful"));
    ASSERT_EQ(true, solution.isCircularSentence("eetcode"));
    ASSERT_EQ(false, solution.isCircularSentence("Leetcode is cool"));
}

}