#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string freqAlphabets(std::string const &s) const
    {
        std::string result;
        for (size_t index = 0; index < s.size(); ++index)
        {
            if ((index + 2) < s.size() && s[index + 2] == '#')
            {
                result.push_back(decryptChar(s, index, 2));
                index += 2;
            }
            else
                result.push_back(decryptChar(s, index, 1));
        }
        return result;
    }

private:
    char decryptChar(std::string const &source, size_t pos, size_t len) const
    {
        int code = 0;
        for (size_t shift = 0; shift < len; ++shift)
            code = 10 * code + (source[pos + shift] - '0');
        return 'a' + (code - 1);
    }
};

}

namespace DecryptStringFromAlphabetToIntegerMappingTask
{

TEST(DecryptStringFromAlphabetToIntegerMappingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("jkab", solution.freqAlphabets("10#11#12"));
    ASSERT_EQ("acz", solution.freqAlphabets("1326#"));
    ASSERT_EQ("y", solution.freqAlphabets("25#"));
    ASSERT_EQ("abcdefghijklmnopqrstuvwxyz", solution.freqAlphabets("12345678910#11#12#13#14#15#16#17#18#19#20#21#22#23#24#25#26#"));
}

}