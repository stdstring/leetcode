#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string reverseWords(std::string const &s) const
    {
        std::string dest;
        size_t index = 0;
        while (index < s.size())
        {
            if (!dest.empty())
            {
                dest.push_back(' ');
                ++index;
            }
            size_t wordLength = 0;
            while ((index + wordLength) < s.size() && s[index + wordLength] != ' ')
                ++wordLength;
            for (size_t wordIndex = 0; wordIndex < wordLength; ++wordIndex)
                dest.push_back(s[index + wordLength - wordIndex - 1]);
            index += wordLength;
        }
        return dest;
    }
};

}

namespace ReverseWordsInStringIIITask
{

TEST(ReverseWordsInStringIIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("s'teL ekat edoCteeL tsetnoc", solution.reverseWords("Let's take LeetCode contest"));
}

}