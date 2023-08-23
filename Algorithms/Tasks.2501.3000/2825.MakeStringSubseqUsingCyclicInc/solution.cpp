#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canMakeSubsequence(std::string const &str1, std::string const &str2) const
    {
        size_t index2 = 0;
        for (size_t index1 = 0; (index1 < str1.size()) && (index2 < str2.size()); ++index1)
        {
            const char ch1 = str1[index1];
            const char nextCh1 = ch1 == 'z' ? 'a' : static_cast<char>(ch1 + 1);
            const char ch2 = str2[index2];
            if ((ch1 == ch2) || (nextCh1 == ch2))
                ++index2;
        }
        return index2 == str2.size();
    }
};

}

namespace MakeStringSubseqUsingCyclicIncTask
{

TEST(MakeStringSubseqUsingCyclicIncTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canMakeSubsequence("abc", "ad"));
    ASSERT_EQ(true, solution.canMakeSubsequence("zc", "ad"));
    ASSERT_EQ(false, solution.canMakeSubsequence("ab", "d"));
}

}