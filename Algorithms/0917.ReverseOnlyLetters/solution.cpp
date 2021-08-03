#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string reverseOnlyLetters(std::string const &s) const
    {
        std::string result(s.size(), ' ');
        size_t frontIndex = 0;
        size_t backIndex = 0;
        while (frontIndex < s.size())
        {
            if (std::isalpha(s[frontIndex]))
            {
                while (!std::isalpha(s[s.size() - 1 - backIndex]))
                    ++backIndex;
                result[frontIndex] = s[s.size() - 1 - backIndex];
                ++backIndex;
            }
            else
                result[frontIndex] = s[frontIndex];
            ++frontIndex;
        }
        return result;
    }
};

}

namespace ReverseOnlyLettersTask
{

TEST(ReverseOnlyLettersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("dc-ba", solution.reverseOnlyLetters("ab-cd"));
    ASSERT_EQ("j-Ih-gfE-dCba", solution.reverseOnlyLetters("a-bC-dEf-ghIj"));
    ASSERT_EQ("Qedo1ct-eeLg=ntse-T!", solution.reverseOnlyLetters("Test1ng-Leet=code-Q!"));
}

}