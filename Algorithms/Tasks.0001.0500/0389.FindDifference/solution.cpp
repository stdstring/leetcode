#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    char findTheDifference(std::string const &s, std::string const &t) const
    {
        const size_t alphabetSize = 26;
        std::vector<int> letters(alphabetSize, 0);
        // fill
        for (char ch : s)
            ++letters[ch - 'a'];
        // find
        for (char ch : t)
        {
            if (letters[ch - 'a'] == 0)
                return ch;
            --letters[ch - 'a'];
        }
        return '\0';
    }
};

}

namespace FindDifferenceTask
{

TEST(FindDifferenceTask, Examples)
{
    const Solution solution;
    ASSERT_EQ('e', solution.findTheDifference("abcd", "abcde"));
    ASSERT_EQ('y', solution.findTheDifference("", "y"));
    ASSERT_EQ('a', solution.findTheDifference("a", "aa"));
    ASSERT_EQ('a', solution.findTheDifference("ae", "aea"));
}

}