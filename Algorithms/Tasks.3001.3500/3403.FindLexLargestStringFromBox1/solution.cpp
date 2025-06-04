#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string answerString(std::string const &word, int numFriends) const
    {
        if (numFriends == 1)
            return word;
        const size_t maxSubstringSize = word.size() - numFriends + 1;
        std::string result;
        for (size_t index = 0; index < word.size(); ++index)
        {
            std::string current(word.substr(index, maxSubstringSize));
            result = std::max(result, current);
        }
        return result;
    }
};

}

namespace FindLexLargestStringFromBox1Task
{

TEST(FindLexLargestStringFromBox1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("dbc", solution.answerString("dbca", 2));
    ASSERT_EQ("g", solution.answerString("gggg", 4));
}

TEST(FindLexLargestStringFromBox1TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("gh", solution.answerString("gh", 1));
}

}