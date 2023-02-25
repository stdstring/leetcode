#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string toGoatLatin(std::string const &s) const
    {
        constexpr char delimiter = ' ';
        std::string dest;
        size_t pos = 0;
        size_t letterIndex = 1;
        while (pos < s.size())
        {
            size_t delimiterPos = s.find(delimiter, pos);
            if (delimiterPos == std::string::npos)
                delimiterPos = s.size();
            if (isVowel(s[pos]))
                dest.append(s, pos, delimiterPos - pos);
            else
                dest.append(s, pos + 1, delimiterPos - pos - 1).push_back(s[pos]);
            dest.append("ma").append(letterIndex++, 'a');
            if (delimiterPos < s.size())
                dest.push_back(' ');
            pos = delimiterPos + 1;
        }
        return dest;
    }

private:
    bool isVowel(char ch) const
    {
        return ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E' || ch == 'i' || ch == 'I' || ch == 'o' || ch == 'O' || ch == 'u' || ch == 'U';
    }
};

}

namespace GoatLatinTask
{

TEST(GoatLatinTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("Imaa peaksmaaa oatGmaaaa atinLmaaaaa", solution.toGoatLatin("I speak Goat Latin"));
    ASSERT_EQ("heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa", solution.toGoatLatin("The quick brown fox jumped over the lazy dog"));
}

}