#include <cctype>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string decodeString(std::string const &s) const
    {
        size_t pos = 0;
        return read(s, pos);
    }

private:
    size_t readCount(std::string const &source, size_t &pos) const
    {
        size_t count = 0;
        while (pos < source.size() && std::isdigit(source[pos]))
            count = 10 * count + (source[pos++] - '0');
        return count == 0 ? 1 : count;
    }

    void repeatSubstring(std::string &dest, std::string const &substring, size_t count) const
    {
        for (size_t repetition = 1; repetition <= count; ++repetition)
            dest.append(substring);
    }

    std::string read(std::string const &source, size_t &pos) const
    {
        std::string dest;
        while (pos < source.size() && source[pos] != ']')
        {
            const size_t count = readCount(source, pos);
            if (source[pos] == '[')
            {
                // read '['
                ++pos;
                // read substring
                std::string substring(read(source, pos));
                // read ']'
                ++pos;
                // repeat substring
                repeatSubstring(dest, substring, count);
            }
            else
                dest.push_back(source[pos++]);
        }
        return dest;
    }
};

}

namespace DecodeStringTask
{

TEST(DecodeStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("aaabcbc", solution.decodeString("3[a]2[bc]"));
    ASSERT_EQ("accaccacc", solution.decodeString("3[a2[c]]"));
    ASSERT_EQ("abcabccdcdcdef", solution.decodeString("2[abc]3[cd]ef"));
    ASSERT_EQ("abccdcdcdxyz", solution.decodeString("abc3[cd]xyz"));
}

}