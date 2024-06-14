#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string compressedString(std::string const &word) const
    {
        std::string result;
        result.reserve(2 * word.size());
        char currentChar = word[0];
        int currentSize = 0;
        for (const char ch : word)
        {
            if ((currentChar != ch) || (currentSize == 9))
            {
                addChar(result, currentChar, currentSize);
                currentChar = ch;
                currentSize = 1;
            }
            else
                ++currentSize;
        }
        addChar(result, currentChar, currentSize);
        return result;
    }

private:
    void addChar(std::string &result, char ch, int count) const
    {
        result.push_back(static_cast<char>('0' + count));
        result.push_back(ch);
    }
};

}

namespace StringCompression3Task
{

TEST(StringCompression3TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("1a1b1c1d1e", solution.compressedString("abcde"));
    ASSERT_EQ("9a5a2b", solution.compressedString("aaaaaaaaaaaaaabb"));
}

}