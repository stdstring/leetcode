#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string reversePrefix(std::string const &word, char ch) const
    {
        const size_t charPos = word.find(ch);
        if (charPos == std::string::npos)
            return word;
        std::string result;
        for (size_t index = 0; index <= charPos; ++index)
            result.push_back(word[charPos - index]);
        result.append(word.substr(charPos + 1));
        return result;
    }
};

}

namespace ReversePrefixOfWordTask
{

TEST(ReversePrefixOfWordTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("dcbaefd", solution.reversePrefix("abcdefd", 'd'));
    ASSERT_EQ("zxyxxe", solution.reversePrefix("xyxzxe", 'z'));
    ASSERT_EQ("abcd", solution.reversePrefix("abcd", 'z'));
}

}
