#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int beautifulSubstrings(std::string const &s, int k) const
    {
        int result = 0;
        for (size_t startIndex = 0; startIndex < s.size(); ++startIndex)
        {
            int vowels = 0;
            int consonants = 0;
            for (size_t endIndex = startIndex; endIndex < s.size(); ++endIndex)
            {
                ++(isVowel(s[endIndex]) ? vowels : consonants);
                if ((vowels == consonants) && ((vowels * consonants) % k == 0))
                    ++result;
            }
        }
        return result;
    }

private:
    [[nodiscard]] bool isVowel(char ch) const
    {
        return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'o') || (ch == 'u');
    }
};

}

namespace CountBeautifulSubstrings1Task
{

TEST(CountBeautifulSubstrings1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.beautifulSubstrings("baeyh", 2));
    ASSERT_EQ(3, solution.beautifulSubstrings("abba", 1));
    ASSERT_EQ(0, solution.beautifulSubstrings("bcdf", 1));
}

}